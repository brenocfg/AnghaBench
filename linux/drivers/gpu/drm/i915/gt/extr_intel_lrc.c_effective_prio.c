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

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int I915_PRIORITY_MASK ; 
 int I915_PRIORITY_NOSEMAPHORE ; 
 int I915_PRIORITY_UNPREEMPTABLE ; 
 int __NO_PREEMPTION ; 
 scalar_t__ __i915_request_has_started (struct i915_request const*) ; 
 scalar_t__ i915_request_has_nopreempt (struct i915_request const*) ; 
 int rq_prio (struct i915_request const*) ; 

__attribute__((used)) static int effective_prio(const struct i915_request *rq)
{
	int prio = rq_prio(rq);

	/*
	 * If this request is special and must not be interrupted at any
	 * cost, so be it. Note we are only checking the most recent request
	 * in the context and so may be masking an earlier vip request. It
	 * is hoped that under the conditions where nopreempt is used, this
	 * will not matter (i.e. all requests to that context will be
	 * nopreempt for as long as desired).
	 */
	if (i915_request_has_nopreempt(rq))
		prio = I915_PRIORITY_UNPREEMPTABLE;

	/*
	 * On unwinding the active request, we give it a priority bump
	 * if it has completed waiting on any semaphore. If we know that
	 * the request has already started, we can prevent an unwanted
	 * preempt-to-idle cycle by taking that into account now.
	 */
	if (__i915_request_has_started(rq))
		prio |= I915_PRIORITY_NOSEMAPHORE;

	/* Restrict mere WAIT boosts from triggering preemption */
	BUILD_BUG_ON(__NO_PREEMPTION & ~I915_PRIORITY_MASK); /* only internal */
	return prio | __NO_PREEMPTION;
}