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
struct kpc_dma_device {unsigned int desc_pool_cnt; int /*<<< orphan*/  irq; int /*<<< orphan*/  desc_pool; struct kpc_dma_descriptor* desc_pool_first; } ;
struct kpc_dma_descriptor {int /*<<< orphan*/  DescNextDescPtr; struct kpc_dma_descriptor* Next; int /*<<< orphan*/  MyDMAAddr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct kpc_dma_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct kpc_dma_device*) ; 
 int /*<<< orphan*/  stop_dma_engine (struct kpc_dma_device*) ; 

void  destroy_dma_engine(struct kpc_dma_device *eng)
{
	struct kpc_dma_descriptor *cur;
	dma_addr_t cur_handle;
	unsigned int i;

	stop_dma_engine(eng);

	cur = eng->desc_pool_first;
	cur_handle = eng->desc_pool_first->MyDMAAddr;

	for (i = 0 ; i < eng->desc_pool_cnt ; i++) {
		struct kpc_dma_descriptor *next = cur->Next;
		dma_addr_t next_handle = cur->DescNextDescPtr;

		dma_pool_free(eng->desc_pool, cur, cur_handle);
		cur_handle = next_handle;
		cur = next;
	}

	dma_pool_destroy(eng->desc_pool);

	free_irq(eng->irq, eng);
}