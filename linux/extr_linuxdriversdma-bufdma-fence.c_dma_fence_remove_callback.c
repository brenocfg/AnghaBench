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
struct dma_fence_cb {int /*<<< orphan*/  node; } ;
struct dma_fence {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

bool
dma_fence_remove_callback(struct dma_fence *fence, struct dma_fence_cb *cb)
{
	unsigned long flags;
	bool ret;

	spin_lock_irqsave(fence->lock, flags);

	ret = !list_empty(&cb->node);
	if (ret)
		list_del_init(&cb->node);

	spin_unlock_irqrestore(fence->lock, flags);

	return ret;
}