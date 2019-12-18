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
struct syncobj_wait_entry {struct dma_fence* fence; int /*<<< orphan*/  node; int /*<<< orphan*/  point; } ;
struct drm_syncobj {int /*<<< orphan*/  lock; int /*<<< orphan*/  cb_list; int /*<<< orphan*/  fence; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 scalar_t__ dma_fence_chain_find_seqno (struct dma_fence**,int /*<<< orphan*/ ) ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 struct dma_fence* dma_fence_get_stub () ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_syncobj_fence_add_wait(struct drm_syncobj *syncobj,
				       struct syncobj_wait_entry *wait)
{
	struct dma_fence *fence;

	if (wait->fence)
		return;

	spin_lock(&syncobj->lock);
	/* We've already tried once to get a fence and failed.  Now that we
	 * have the lock, try one more time just to be sure we don't add a
	 * callback when a fence has already been set.
	 */
	fence = dma_fence_get(rcu_dereference_protected(syncobj->fence, 1));
	if (!fence || dma_fence_chain_find_seqno(&fence, wait->point)) {
		dma_fence_put(fence);
		list_add_tail(&wait->node, &syncobj->cb_list);
	} else if (!fence) {
		wait->fence = dma_fence_get_stub();
	} else {
		wait->fence = fence;
	}
	spin_unlock(&syncobj->lock);
}