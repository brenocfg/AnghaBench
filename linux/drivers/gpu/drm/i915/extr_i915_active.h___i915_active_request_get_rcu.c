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
struct i915_request {int dummy; } ;
struct i915_active_request {int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 struct i915_request* i915_request_get_rcu (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 struct i915_request* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct i915_request* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct i915_request* rcu_pointer_handoff (struct i915_request*) ; 

__attribute__((used)) static inline struct i915_request *
__i915_active_request_get_rcu(const struct i915_active_request *active)
{
	/*
	 * Performing a lockless retrieval of the active request is super
	 * tricky. SLAB_TYPESAFE_BY_RCU merely guarantees that the backing
	 * slab of request objects will not be freed whilst we hold the
	 * RCU read lock. It does not guarantee that the request itself
	 * will not be freed and then *reused*. Viz,
	 *
	 * Thread A			Thread B
	 *
	 * rq = active.request
	 *				retire(rq) -> free(rq);
	 *				(rq is now first on the slab freelist)
	 *				active.request = NULL
	 *
	 *				rq = new submission on a new object
	 * ref(rq)
	 *
	 * To prevent the request from being reused whilst the caller
	 * uses it, we take a reference like normal. Whilst acquiring
	 * the reference we check that it is not in a destroyed state
	 * (refcnt == 0). That prevents the request being reallocated
	 * whilst the caller holds on to it. To check that the request
	 * was not reallocated as we acquired the reference we have to
	 * check that our request remains the active request across
	 * the lookup, in the same manner as a seqlock. The visibility
	 * of the pointer versus the reference counting is controlled
	 * by using RCU barriers (rcu_dereference and rcu_assign_pointer).
	 *
	 * In the middle of all that, we inspect whether the request is
	 * complete. Retiring is lazy so the request may be completed long
	 * before the active tracker is updated. Querying whether the
	 * request is complete is far cheaper (as it involves no locked
	 * instructions setting cachelines to exclusive) than acquiring
	 * the reference, so we do it first. The RCU read lock ensures the
	 * pointer dereference is valid, but does not ensure that the
	 * seqno nor HWS is the right one! However, if the request was
	 * reallocated, that means the active tracker's request was complete.
	 * If the new request is also complete, then both are and we can
	 * just report the active tracker is idle. If the new request is
	 * incomplete, then we acquire a reference on it and check that
	 * it remained the active request.
	 *
	 * It is then imperative that we do not zero the request on
	 * reallocation, so that we can chase the dangling pointers!
	 * See i915_request_alloc().
	 */
	do {
		struct i915_request *request;

		request = rcu_dereference(active->request);
		if (!request || i915_request_completed(request))
			return NULL;

		/*
		 * An especially silly compiler could decide to recompute the
		 * result of i915_request_completed, more specifically
		 * re-emit the load for request->fence.seqno. A race would catch
		 * a later seqno value, which could flip the result from true to
		 * false. Which means part of the instructions below might not
		 * be executed, while later on instructions are executed. Due to
		 * barriers within the refcounting the inconsistency can't reach
		 * past the call to i915_request_get_rcu, but not executing
		 * that while still executing i915_request_put() creates
		 * havoc enough.  Prevent this with a compiler barrier.
		 */
		barrier();

		request = i915_request_get_rcu(request);

		/*
		 * What stops the following rcu_access_pointer() from occurring
		 * before the above i915_request_get_rcu()? If we were
		 * to read the value before pausing to get the reference to
		 * the request, we may not notice a change in the active
		 * tracker.
		 *
		 * The rcu_access_pointer() is a mere compiler barrier, which
		 * means both the CPU and compiler are free to perform the
		 * memory read without constraint. The compiler only has to
		 * ensure that any operations after the rcu_access_pointer()
		 * occur afterwards in program order. This means the read may
		 * be performed earlier by an out-of-order CPU, or adventurous
		 * compiler.
		 *
		 * The atomic operation at the heart of
		 * i915_request_get_rcu(), see dma_fence_get_rcu(), is
		 * atomic_inc_not_zero() which is only a full memory barrier
		 * when successful. That is, if i915_request_get_rcu()
		 * returns the request (and so with the reference counted
		 * incremented) then the following read for rcu_access_pointer()
		 * must occur after the atomic operation and so confirm
		 * that this request is the one currently being tracked.
		 *
		 * The corresponding write barrier is part of
		 * rcu_assign_pointer().
		 */
		if (!request || request == rcu_access_pointer(active->request))
			return rcu_pointer_handoff(request);

		i915_request_put(request);
	} while (1);
}