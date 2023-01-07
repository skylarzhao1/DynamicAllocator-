#include<stdio.h>
#include<stddef.h>

char mymemory[8000];

struct block{
 size_t size;
 int free;
 struct block *next; 
};

typedef struct block block;

 block *list=(void*)mymemory;


void initmemory()
{
  list->size=8000-sizeof(struct block);
 list->next=NULL;
 list->free=1;
}
// void split( block *slotToBeSplitted,size_t size)
// when the allocated space smaller than the freee space,

void split( block *slotToBeSplitted,size_t size)
{


struct block *new=(void*)((void*)slotToBeSplitted+size+sizeof(struct block));
new->free=1;
new->size=(slotToBeSplitted->size)-size-sizeof(struct block);

new->next=slotToBeSplitted->next;
slotToBeSplitted->size=size;
slotToBeSplitted->free=0;
slotToBeSplitted->next=new;}



void *NewMalloc(size_t allocsSize)
{
 block *curr;
 block *prev;
 void *res;
 curr=list;


 if(!(list->size)){ 
 initmemory();
  
 }





 //TO DO
 //Find a chunk with enough free space


  while(((curr->free)==0||(curr->size)<allocsSize)&&(curr->next!=NULL))
  
  
  
  {
 prev=curr;
  curr=curr->next;
 

}








 if((curr->size)==allocsSize){

curr->free=0;
  res=(void*)(++curr);
  return res;



printf("curr size is: %d\n\n", (int)curr->size);

 


}

//else if?

if((curr->size)>(allocsSize+sizeof(struct block))){
 split(curr,allocsSize);
  res=(void*)(++curr);
 
  return res;

}else{

 res=NULL;
  return res;

}




}



void coalesce(){
 struct block *curr;
 struct block*prev;
 curr=list;
 //TO DO
 //Coalesce consequtive free blocks
 while((curr->next)!=NULL){
  if((curr->free) && (curr->next->free)){
   curr->size+=(curr->next->size)+sizeof(struct block);
   curr->next=curr->next->next;
  }
  prev=curr;
  curr=curr->next;
 }
}


 


void NewFree(void* ptr){
  //TO DO
  //Check if the pointer is in a valid range
  //If yes, free the block and call coalesce
 if(((void*)mymemory<=ptr)&&(ptr<=(void*)(mymemory+8000))){
  struct block* current=ptr;
  --current;
  current->free=1;
  coalesce();
 }
 
}








int main(){
 
 if(!(list->size))
 {
  initmemory();
  printf("\n\n--Memory Initialization Completed--\n");
  printf("Initial size is: %d\n\n", (int)list->size);
 }


 int *p=(int*)NewMalloc(800);
 printf("\n");
 char *q=(char*)NewMalloc(250*sizeof(char));
 printf("\n");
 int *r=(int*)NewMalloc(1000*sizeof(int));
 printf("\n");
 NewFree(p);
 printf("\n");
 char *w=(char*)NewMalloc(1000);
 printf("\n");
 NewFree(r);
 printf("\n");
 int *k=(int*)NewMalloc(1500*sizeof(int));
 printf("\n");

}