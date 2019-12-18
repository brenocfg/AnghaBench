#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_cs {scalar_t__ wakeref_serial; scalar_t__ serial; int /*<<< orphan*/  kernel_context; int /*<<< orphan*/  wakeref; int /*<<< orphan*/  gt; } ;
struct TYPE_3__ {int /*<<< orphan*/  priority; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct i915_request {TYPE_2__ sched; int /*<<< orphan*/  timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  I915_PRIORITY_UNPREEMPTABLE ; 
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int /*<<< orphan*/  __i915_request_commit (struct i915_request*) ; 
 struct i915_request* __i915_request_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_request_queue (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __intel_wakeref_defer_park (int /*<<< orphan*/ *) ; 
 unsigned long __timeline_mark_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __timeline_mark_unlock (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  i915_request_add_active_barriers (struct i915_request*) ; 
 scalar_t__ intel_gt_is_wedged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_timeline_enter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool switch_to_kernel_context(struct intel_engine_cs *engine)
{
	struct i915_request *rq;
	unsigned long flags;
	bool result = true;

	/* Already inside the kernel context, safe to power down. */
	if (engine->wakeref_serial == engine->serial)
		return true;

	/* GPU is pointing to the void, as good as in the kernel context. */
	if (intel_gt_is_wedged(engine->gt))
		return true;

	/*
	 * Note, we do this without taking the timeline->mutex. We cannot
	 * as we may be called while retiring the kernel context and so
	 * already underneath the timeline->mutex. Instead we rely on the
	 * exclusive property of the __engine_park that prevents anyone
	 * else from creating a request on this engine. This also requires
	 * that the ring is empty and we avoid any waits while constructing
	 * the context, as they assume protection by the timeline->mutex.
	 * This should hold true as we can only park the engine after
	 * retiring the last request, thus all rings should be empty and
	 * all timelines idle.
	 */
	flags = __timeline_mark_lock(engine->kernel_context);

	rq = __i915_request_create(engine->kernel_context, GFP_NOWAIT);
	if (IS_ERR(rq))
		/* Context switch failed, hope for the best! Maybe reset? */
		goto out_unlock;

	intel_timeline_enter(rq->timeline);

	/* Check again on the next retirement. */
	engine->wakeref_serial = engine->serial + 1;
	i915_request_add_active_barriers(rq);

	/* Install ourselves as a preemption barrier */
	rq->sched.attr.priority = I915_PRIORITY_UNPREEMPTABLE;
	__i915_request_commit(rq);

	/* Release our exclusive hold on the engine */
	__intel_wakeref_defer_park(&engine->wakeref);
	__i915_request_queue(rq, NULL);

	result = false;
out_unlock:
	__timeline_mark_unlock(engine->kernel_context, flags);
	return result;
}