
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

static int flag =1;
struct AdptArray_ {
    PElement* arr;
    int size;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
};

//create
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC printFunc)
{
	PAdptArray p = (PAdptArray)malloc(sizeof(struct AdptArray_));
	if (p == NULL){
		flag=-1;
		return NULL;
	}
	p->arr = (PElement*) malloc(sizeof(PElement));
    if (!p->arr) {
        free(p);
        return NULL;
    }
	
	p->arr[0] = NULL;
	p->delFunc = delFunc_;
	p->copyFunc = copyFunc_;
    p->printFunc=printFunc;
    p->size = 1;
	return p;
}
//delete
void DeleteAdptArray(PAdptArray p)
{
	int i;
    int len= p->size;
	if (p == NULL)
		return;
	for(i = 0; i < len; ++i)
	{
		if (p->arr[i])
			p->delFunc((p->arr)[i]);
	}
	free(p->arr);
	free(p);
}


//set
Result SetAdptArrayAt(PAdptArray p, int idx, PElement e)
{
    if (p == NULL || idx < 0)
        return FAIL;

    if (idx >= p->size) {
        int sizeNew = idx + 1;
        PElement* newArray = (PElement*) realloc(p->arr, sizeNew * sizeof(PElement));
        if (newArray == NULL)
            return FAIL;

        p->arr = newArray;
        for (int i = p->size; i < idx; i++) {
            p->arr[i] = NULL;
        }
        p->size = sizeNew;
    }

	p->arr[idx]=p->copyFunc(e);
    return SUCCESS;
}

//getSize
int GetAdptArraySize(PAdptArray pArr){
	if (flag==-1)
	{
		return flag;
	}
    return pArr->size;
	
}
//ArrayAt
PElement GetAdptArrayAt(PAdptArray pArr, int i){
	if (pArr==NULL|| pArr->size<= i||i<0||pArr->arr[i]==NULL)
	{
		return NULL;
	}
	return pArr->copyFunc(pArr->arr[i]);
}

//print
void PrintDB(PAdptArray pArr){
	if (pArr==NULL)
		return;
	for (int i = 0; i < pArr->size; i++)
	{
		if (pArr-> arr[i])
		{
			pArr->printFunc(pArr->arr[i]);
		}	
	}
}
