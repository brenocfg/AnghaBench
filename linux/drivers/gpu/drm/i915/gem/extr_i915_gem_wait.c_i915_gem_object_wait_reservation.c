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
struct dma_resv {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 unsigned int I915_WAIT_ALL ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (struct dma_resv*,int /*<<< orphan*/ *) ; 
 struct dma_fence* dma_resv_get_excl_rcu (struct dma_resv*) ; 
 int dma_resv_get_fences_rcu (struct dma_resv*,struct dma_fence**,unsigned int*,struct dma_fence***) ; 
 scalar_t__ dma_resv_test_signaled_rcu (struct dma_resv*,int) ; 
 scalar_t__ dma_resv_trylock (struct dma_resv*) ; 
 int /*<<< orphan*/  dma_resv_unlock (struct dma_resv*) ; 
 long i915_gem_object_wait_fence (struct dma_fence*,unsigned int,long) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 

__attribute__((used)) static long
i915_gem_object_wait_reservation(struct dma_resv *resv,
				 unsigned int flags,
				 long timeout)
{
	struct dma_fence *excl;
	bool prune_fences = false;

	if (flags & I915_WAIT_ALL) {
		struct dma_fence **shared;
		unsigned int count, i;
		int ret;

		ret = dma_resv_get_fences_rcu(resv,
							&excl, &count, &shared);
		if (ret)
			return ret;

		for (i = 0; i < count; i++) {
			timeout = i915_gem_object_wait_fence(shared[i],
							     flags, timeout);
			if (timeout < 0)
				break;

			dma_fence_put(shared[i]);
		}

		for (; i < count; i++)
			dma_fence_put(shared[i]);
		kfree(shared);

		/*
		 * If both shared fences and an exclusive fence exist,
		 * then by construction the shared fences must be later
		 * than the exclusive fence. If we successfully wait for
		 * all the shared fences, we know that the exclusive fence
		 * must all be signaled. If all the shared fences are
		 * signaled, we can prune the array and recover the
		 * floating references on the fences/requests.
		 */
		prune_fences = count && timeout >= 0;
	} else {
		excl = dma_resv_get_excl_rcu(resv);
	}

	if (excl && timeout >= 0)
		timeout = i915_gem_object_wait_fence(excl, flags, timeout);

	dma_fence_put(excl);

	/*
	 * Opportunistically prune the fences iff we know they have *all* been
	 * signaled.
	 */
	if (prune_fences && dma_resv_trylock(resv)) {
		if (dma_resv_test_signaled_rcu(resv, true))
			dma_resv_add_excl_fence(resv, NULL);
		dma_resv_unlock(resv);
	}

	return timeout;
}