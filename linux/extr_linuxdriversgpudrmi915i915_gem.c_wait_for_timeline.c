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
struct i915_timeline {int /*<<< orphan*/  last_request; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 unsigned int I915_WAIT_FOR_IDLE_BOOST ; 
 int /*<<< orphan*/  gen6_rps_boost (struct i915_request*,int /*<<< orphan*/ *) ; 
 struct i915_request* i915_gem_active_get_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 long i915_request_wait (struct i915_request*,unsigned int,long) ; 

__attribute__((used)) static long wait_for_timeline(struct i915_timeline *tl,
			      unsigned int flags, long timeout)
{
	struct i915_request *rq;

	rq = i915_gem_active_get_unlocked(&tl->last_request);
	if (!rq)
		return timeout;

	/*
	 * "Race-to-idle".
	 *
	 * Switching to the kernel context is often used a synchronous
	 * step prior to idling, e.g. in suspend for flushing all
	 * current operations to memory before sleeping. These we
	 * want to complete as quickly as possible to avoid prolonged
	 * stalls, so allow the gpu to boost to maximum clocks.
	 */
	if (flags & I915_WAIT_FOR_IDLE_BOOST)
		gen6_rps_boost(rq, NULL);

	timeout = i915_request_wait(rq, flags, timeout);
	i915_request_put(rq);

	return timeout;
}