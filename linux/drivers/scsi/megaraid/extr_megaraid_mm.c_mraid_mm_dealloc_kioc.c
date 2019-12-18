#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pool_index; int free_buf; int /*<<< orphan*/  list; int /*<<< orphan*/  buf_paddr; int /*<<< orphan*/  buf_vaddr; } ;
typedef  TYPE_1__ uioc_t ;
struct TYPE_7__ {int /*<<< orphan*/  kioc_semaphore; int /*<<< orphan*/  kioc_pool_lock; int /*<<< orphan*/  kioc_pool; TYPE_3__* dma_pool_list; } ;
typedef  TYPE_2__ mraid_mmadp_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; scalar_t__ in_use; int /*<<< orphan*/  handle; } ;
typedef  TYPE_3__ mm_dmapool_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mraid_mm_dealloc_kioc(mraid_mmadp_t *adp, uioc_t *kioc)
{
	mm_dmapool_t	*pool;
	unsigned long	flags;

	if (kioc->pool_index != -1) {
		pool = &adp->dma_pool_list[kioc->pool_index];

		/* This routine may be called in non-isr context also */
		spin_lock_irqsave(&pool->lock, flags);

		/*
		 * While attaching the dma buffer, if we didn't get the 
		 * required buffer from the pool, we would have allocated 
		 * it at the run time and set the free_buf flag. We must 
		 * free that buffer. Otherwise, just mark that the buffer is 
		 * not in use
		 */
		if (kioc->free_buf == 1)
			dma_pool_free(pool->handle, kioc->buf_vaddr, 
							kioc->buf_paddr);
		else
			pool->in_use = 0;

		spin_unlock_irqrestore(&pool->lock, flags);
	}

	/* Return the kioc to the free pool */
	spin_lock_irqsave(&adp->kioc_pool_lock, flags);
	list_add(&kioc->list, &adp->kioc_pool);
	spin_unlock_irqrestore(&adp->kioc_pool_lock, flags);

	/* increment the free kioc count */
	up(&adp->kioc_semaphore);

	return;
}