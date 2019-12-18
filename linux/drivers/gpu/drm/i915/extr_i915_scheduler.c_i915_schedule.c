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
struct i915_sched_attr {int dummy; } ;
struct i915_request {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_schedule (int /*<<< orphan*/ *,struct i915_sched_attr const*) ; 
 int /*<<< orphan*/  schedule_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void i915_schedule(struct i915_request *rq, const struct i915_sched_attr *attr)
{
	spin_lock_irq(&schedule_lock);
	__i915_schedule(&rq->sched, attr);
	spin_unlock_irq(&schedule_lock);
}