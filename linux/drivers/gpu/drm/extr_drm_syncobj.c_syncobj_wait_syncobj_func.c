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
struct syncobj_wait_entry {int /*<<< orphan*/  node; int /*<<< orphan*/  task; struct dma_fence* fence; int /*<<< orphan*/  point; } ;
struct drm_syncobj {int /*<<< orphan*/  lock; int /*<<< orphan*/  fence; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 scalar_t__ dma_fence_chain_find_seqno (struct dma_fence**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 struct dma_fence* dma_fence_get_stub () ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void syncobj_wait_syncobj_func(struct drm_syncobj *syncobj,
				      struct syncobj_wait_entry *wait)
{
	struct dma_fence *fence;

	/* This happens inside the syncobj lock */
	fence = rcu_dereference_protected(syncobj->fence,
					  lockdep_is_held(&syncobj->lock));
	dma_fence_get(fence);
	if (!fence || dma_fence_chain_find_seqno(&fence, wait->point)) {
		dma_fence_put(fence);
		return;
	} else if (!fence) {
		wait->fence = dma_fence_get_stub();
	} else {
		wait->fence = fence;
	}

	wake_up_process(wait->task);
	list_del_init(&wait->node);
}