#include <stdio.h>
#include <stdlib.h>

/* declare global var's */
//int main_memory_size = 0;
int memory_size = 0;
int number_of_lines = 0;
int cache_size = 0;
int block_size = 0;
/* define structure of dynamic cache and initialize var */
    struct node{
        int tag;
        int* block;

    } * cache = NULL;
    typedef struct node line;
/* define dynamic array for main memory */
int* main_memory = NULL;

/****************************************************************/
void parameters()
{
    /* declare local var's */
    int i;
    /* Prompt for main memory size, cache size, block size */
    printf("Enter main memory size (words): ");
    scanf("%d", &memory_size);
    printf("Enter cache size (words): ");
    scanf("%d", &cache_size);
    printf("Enter block size (words/blocks): ");
    scanf("%d", &block_size);

    number_of_lines = cache_size/block_size;

    /* allocate and initialize main memory--value at index i = size of main memory-i*/
    main_memory = (int *)malloc(memory_size * sizeof(int));
    for(i=0; i<memory_size; i++){
        main_memory[i] = memory_size - i;
    }
    /* allocate memory for cache based on number of lines in cache*/
    /* initialize each tag to -1 and each block to NULL */
    cache = (line *)malloc(number_of_lines * sizeof(line));

    for (i =0; i< number_of_lines; i++){
        cache[i].block = NULL;
        cache[i].tag = -1;
    }

}


/****************************************************************/
void  access_cache()
{
    /* declare local var's */
//        _Bool read_or_write;
    int read_or_write = 0;
    int memory_address = 0;
    int tag = 0;
    int block = 0;
    int word = 0;
    int i = 0;
    int base = 0;
    int data = 0;
    /* Prompt for read/write signal */
        printf("Enter 0 for read or 1 for write: ");
        scanf("%d", &read_or_write);


    /* Prompt for main memory address to read/write */
//    what if they type 2?
//    printf("which main memory address would you like to read/write from/to");
//    scanf("%d", &memory_address);

    if (read_or_write == 0){
        /*if write: prompt for data to write*/
        printf("Enter main memory address to read from: ");
        scanf("%d", &memory_address);

    }
    if (read_or_write == 1){
        printf("Enter main memory address to write to: ");
        scanf("%d", &memory_address);

        printf("Enter value to write: ");
        scanf("%d", &data);
    }


    /* Translate main mem addr to cache addr fields*/
    tag = memory_address/ cache_size;
    block = (memory_address%cache_size) / block_size;
    word = memory_address % block_size;
//    base = (memory_address % cache_size) / block_size;

    base = (memory_address / block_size) * block_size;
//    base = memory_address - word;
//    int line = memory_address%cache_size/block_size;

    /* Case 1: MISS--BLOCK NOT ALLOCATED */
    if (cache[block].tag == -1){

//        if (block != cache->tag){}

// if casted to int it keeps going but if not casted then once it hits line 123 it quits. due to segmentation fault
        cache[block].block = (int *) malloc(block_size* sizeof(int*));

    /* Allocate cache block based on block size */

    }


    /* Case 2: MISS--NON-MATCHING TAGS */
    if (cache[block].tag != tag){
        /* Print message of Read/Write miss */
        if(read_or_write == 0){
            printf("Block %d  READ MISS! \n", block);
        }

        if (read_or_write == 1){
            printf("Block %d  WRITE MISS! \n", block);

//            cache[block].block[word] = data;
            main_memory[memory_address] = data;
        }


        /* Overwrite tag */

        cache[block].tag = tag;

        /* Transfer equivalent block of main memory to cache--one word at a time */
            for (i = 0; i< block_size; i++){
                cache[block].block[i] = main_memory[base+i];
            }

    }

    /* Case 3:HIT DUE TO MATCHING TAGS */
    else {
        /*print message of Read/Write hit*/
        if(read_or_write == 0){
            printf("Block %d :  READ HIT! \n", block);
        }

        if(read_or_write == 1){
            printf("Block %d :  WRITE HIT! \n", block);

//            cache[block].block[word] = data;
            main_memory[memory_address] = data;
        }
    }
    cache[block].block[word] = data;
        /*transfer the data to the cache on write*/
/*        if(read_or_write == 1){

        }*/

}

/****************************************************************/
void display_contents_of_block()
{
    /* declare local var's */
    int i;
    int block;

    /*  prompt for block to write contents of */
    printf("Enter block (0-127) to display: ");
    scanf("%d", &block);

    /* print contents of each word of requested block */
/*
        for(i =0; i < block_size; i++){
            printf("...\t", cache[block].block[i]);
        }
*/

    printf("Block:%d, Tag:%d \n", block, cache[block].tag);

    printf("\n|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");

    printf("|Word");

    for(i=0; i < block_size; i++){
        printf("\t |%d",i);
    }

    printf("\n");
    printf("|Data");

    for(i=0; i < block_size; i++) {
        printf("\t |%d", cache[block].block[i]);
    }

    printf("\n|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");


}

/****************************************************************/
int main()
{
/* declare local var's */
    int choice = 0;
/* until program exits, print menu, select choice via switch statement and call appropriate function*/


    printf("------------------------------------ \n");
    printf("Please pick from the following choices \n");

    printf("Press 1: to Enter parameters  \n");
    printf("Press 2: to Access cache  \n");
    printf("Press 3: to Display contents of block  \n");
    printf("Press 4: to quit \n");

    scanf("%d", &choice);
    printf("------------------------------------ \n");


    switch (choice){
        case 1:
            parameters();
            main();
            break;
        case 2:
            access_cache();
            main();
            break;
        case 3:
            display_contents_of_block();
            main();
            break;
        case 4:
            break;
        default:
            printf("Not a valid choice. Please try again. \n");
            main();
    }


    return 1;
}
