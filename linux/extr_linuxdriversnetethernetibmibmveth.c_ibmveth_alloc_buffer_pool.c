#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ibmveth_buff_pool {int* free_map; int size; int* dma_addr; scalar_t__ consumer_index; scalar_t__ producer_index; int /*<<< orphan*/  available; void* skbuff; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmveth_alloc_buffer_pool(struct ibmveth_buff_pool *pool)
{
	int i;

	pool->free_map = kmalloc_array(pool->size, sizeof(u16), GFP_KERNEL);

	if (!pool->free_map)
		return -1;

	pool->dma_addr = kcalloc(pool->size, sizeof(dma_addr_t), GFP_KERNEL);
	if (!pool->dma_addr) {
		kfree(pool->free_map);
		pool->free_map = NULL;
		return -1;
	}

	pool->skbuff = kcalloc(pool->size, sizeof(void *), GFP_KERNEL);

	if (!pool->skbuff) {
		kfree(pool->dma_addr);
		pool->dma_addr = NULL;

		kfree(pool->free_map);
		pool->free_map = NULL;
		return -1;
	}

	for (i = 0; i < pool->size; ++i)
		pool->free_map[i] = i;

	atomic_set(&pool->available, 0);
	pool->producer_index = 0;
	pool->consumer_index = 0;

	return 0;
}