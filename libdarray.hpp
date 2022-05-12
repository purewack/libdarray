#pragma once

#ifndef LOGL
#define LOGL(X)
#endif
#ifndef LOG
#define LOG(X)
#endif

template <typename T> 
struct DArray {
    T* buf;
    unsigned int buf_len;
    unsigned int count;
    unsigned int chunk_size = 1;
};

template <typename T>
void add_space(DArray<T> &a){
    const int bss = a.chunk_size;
    if(a.buf_len == 0){
        a.buf = (token_t*)malloc(sizeof(token_t)*bss);
        a.buf_len = bss;
        a.count = 0;
    }
    else if(a.count == a.buf_len){
        a.buf_len += bss;
        a.buf = (token_t*)realloc(a.buf, sizeof(token_t) * (a.buf_len));
    }
}

template <typename T> 
void darray_clear(DArray<T> &a){
    if(a.buf) free(a.buf);
    a.buf_len = 0;
    a.count = 0;
}

template <typename T> 
void darray_push(DArray<T> &a, T t){
    add_space(a);

    a.buf[a.count] = t;
    a.count++;
    return;
}
template <typename T> 
void darray_pop(DArray<T> &a){
    if(a.count == 0) return;
    a.count--;
}

template <typename T> 
void darray_insert(DArray<T> &a, T t, unsigned int i){
    if(i >= a.count) return darray_push(a,t);
    
    if(a.count+1 > a.buf_len) add_space(a);
    
    for(int j=a.count; j>i; j--){
        auto aa = a.buf[j-1];
        a.buf[j] = aa;
    }
    a.buf[i] = t;
    a.count++;
    
    return;
}
template <typename T> 
void darray_remove(DArray<T> &a, int i){
    if(a.count == 0) return;
    for(int j=i; j<(a.count); j++){
        T aa = a.buf[j+1];
        a.buf[j] = aa;
    }
    a.count--;
}


template <typename T> 
struct SArray{
    T* buf;
    unsigned int count;
    unsigned int lim;

    template <typename T> 
    void clear(SArray<T> &array);
    template <typename T> 
    void sarray_push(SArray<T> &a, T t);
};

template <typename T> 
void SArray::clear(SArray<T> &a){
    a.count = 0;
}

template <typename T> 
void sarray_push(SArray<T> &a, T t){
    if(a.count >= a.lim) return;

    a.buf[a.count] = t;
    a.count++;
    return;
}

template <typename T> 
void sarray_pop(SArray<T> &a){
    if(a.count == 0) return;
    a.count--;
}

template <typename T> 
void sarray_insert(SArray<T> &a, T t, unsigned int i){
    if(i >= a.count) return sarray_push(a,t);

    for(int j=a.count; j>i; j--){
        auto aa = a.buf[j-1];
        a.buf[j] = aa;
    }
    a.buf[i] = t;
    a.count++;
    
    return;
}
template <typename T> 
void sarray_remove(SArray<T> &a, int i){
    if(a.count == 0) return;
    for(int j=i; j<(a.count); j++){
        auto aa = a.buf[j+1];
        a.buf[j] = aa;
    }
    a.count--;
}