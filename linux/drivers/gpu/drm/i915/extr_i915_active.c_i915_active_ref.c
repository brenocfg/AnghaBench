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
struct intel_timeline {int /*<<< orphan*/  mutex; } ;
struct i915_request {int dummy; } ;
struct i915_active_request {int /*<<< orphan*/  link; int /*<<< orphan*/  request; } ;
struct i915_active {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __active_del_barrier (struct i915_active*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_active_request_set (struct i915_active_request*,struct i915_request*) ; 
 struct i915_active_request* active_instance (struct i915_active*,struct intel_timeline*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int i915_active_acquire (struct i915_active*) ; 
 int /*<<< orphan*/  i915_active_release (struct i915_active*) ; 
 int /*<<< orphan*/  i915_active_request_isset (struct i915_active_request*) ; 
 scalar_t__ is_barrier (struct i915_active_request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_from_active (struct i915_active_request*) ; 

int i915_active_ref(struct i915_active *ref,
		    struct intel_timeline *tl,
		    struct i915_request *rq)
{
	struct i915_active_request *active;
	int err;

	lockdep_assert_held(&tl->mutex);

	/* Prevent reaping in case we malloc/wait while building the tree */
	err = i915_active_acquire(ref);
	if (err)
		return err;

	active = active_instance(ref, tl);
	if (!active) {
		err = -ENOMEM;
		goto out;
	}

	if (is_barrier(active)) { /* proto-node used by our idle barrier */
		/*
		 * This request is on the kernel_context timeline, and so
		 * we can use it to substitute for the pending idle-barrer
		 * request that we want to emit on the kernel_context.
		 */
		__active_del_barrier(ref, node_from_active(active));
		RCU_INIT_POINTER(active->request, NULL);
		INIT_LIST_HEAD(&active->link);
	} else {
		if (!i915_active_request_isset(active))
			atomic_inc(&ref->count);
	}
	GEM_BUG_ON(!atomic_read(&ref->count));
	__i915_active_request_set(active, rq);

out:
	i915_active_release(ref);
	return err;
}