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
struct reservation_object {int /*<<< orphan*/  seq; } ;
struct intel_rps_client {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 unsigned int I915_WAIT_ALL ; 
 unsigned int __read_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long i915_gem_object_wait_fence (struct dma_fence*,unsigned int,long,struct intel_rps_client*) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 
 int /*<<< orphan*/  reservation_object_add_excl_fence (struct reservation_object*,int /*<<< orphan*/ *) ; 
 struct dma_fence* reservation_object_get_excl_rcu (struct reservation_object*) ; 
 int reservation_object_get_fences_rcu (struct reservation_object*,struct dma_fence**,unsigned int*,struct dma_fence***) ; 
 scalar_t__ reservation_object_trylock (struct reservation_object*) ; 
 int /*<<< orphan*/  reservation_object_unlock (struct reservation_object*) ; 

__attribute__((used)) static long
i915_gem_object_wait_reservation(struct reservation_object *resv,
				 unsigned int flags,
				 long timeout,
				 struct intel_rps_client *rps_client)
{
	unsigned int seq = __read_seqcount_begin(&resv->seq);
	struct dma_fence *excl;
	bool prune_fences = false;

	if (flags & I915_WAIT_ALL) {
		struct dma_fence **shared;
		unsigned int count, i;
		int ret;

		ret = reservation_object_get_fences_rcu(resv,
							&excl, &count, &shared);
		if (ret)
			return ret;

		for (i = 0; i < count; i++) {
			timeout = i915_gem_object_wait_fence(shared[i],
							     flags, timeout,
							     rps_client);
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
		excl = reservation_object_get_excl_rcu(resv);
	}

	if (excl && timeout >= 0)
		timeout = i915_gem_object_wait_fence(excl, flags, timeout,
						     rps_client);

	dma_fence_put(excl);

	/*
	 * Opportunistically prune the fences iff we know they have *all* been
	 * signaled and that the reservation object has not been changed (i.e.
	 * no new fences have been added).
	 */
	if (prune_fences && !__read_seqcount_retry(&resv->seq, seq)) {
		if (reservation_object_trylock(resv)) {
			if (!__read_seqcount_retry(&resv->seq, seq))
				reservation_object_add_excl_fence(resv, NULL);
			reservation_object_unlock(resv);
		}
	}

	return timeout;
}