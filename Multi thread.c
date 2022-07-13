#include <pthread.h>
#include <stdio.h>
#include <time.h>
int prime[5133];
int counter = 0;

void *compute_prime(void *arg) {
  int candidate = *((int *)arg);
  int end = candidate + 10000;
  int count=1;
  while (1){
    int factor, is_prime = 1;
    for (factor = 2; factor < candidate; ++factor){
      if (candidate % factor == 0){
        is_prime = 0;
        break;
      }
    }
    if (is_prime){
      prime[counter++] = candidate;
    }
    if (candidate > end){ return NULL;}
    ++candidate;
  }
  //return NULL;
}
int main() {
  double time_spent = 0.0;
  clock_t begin = clock();
  pthread_t thread[5];
  int table[5] = {2,10000,20000,30000,40000};
  for(int i = 0;i<5;i++){
    pthread_create(&thread[i], NULL, &compute_prime, &table[i]);
  }
  for(int i = 0;i<5;i++){
  pthread_join(thread[i], NULL);
  }
  for(int i = 0;i<5132;i++){
    printf("The prime number is % d.\n", prime[i]);
  }
  time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
  printf("RUNTIME %.5f s\n", time_spent);
  return 0;
}