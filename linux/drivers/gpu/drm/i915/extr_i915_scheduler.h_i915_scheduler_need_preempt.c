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

/* Variables and functions */
 scalar_t__ I915_PRIORITY_NORMAL ; 
 int max (scalar_t__,int) ; 

__attribute__((used)) static inline bool i915_scheduler_need_preempt(int prio, int active)
{
	/*
	 * Allow preemption of low -> normal -> high, but we do
	 * not allow low priority tasks to preempt other low priority
	 * tasks under the impression that latency for low priority
	 * tasks does not matter (as much as background throughput),
	 * so kiss.
	 *
	 * More naturally we would write
	 *	prio >= max(0, last);
	 * except that we wish to prevent triggering preemption at the same
	 * priority level: the task that is running should remain running
	 * to preserve FIFO ordering of dependencies.
	 */
	return prio > max(I915_PRIORITY_NORMAL - 1, active);
}