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
struct TYPE_3__ {int /*<<< orphan*/  priority; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct i915_request {TYPE_2__ sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (unsigned int) ; 
 unsigned int I915_PRIORITY_MASK ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bump_priority (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  schedule_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i915_schedule_bump_priority(struct i915_request *rq, unsigned int bump)
{
	unsigned long flags;

	GEM_BUG_ON(bump & ~I915_PRIORITY_MASK);
	if (READ_ONCE(rq->sched.attr.priority) & bump)
		return;

	spin_lock_irqsave(&schedule_lock, flags);
	__bump_priority(&rq->sched, bump);
	spin_unlock_irqrestore(&schedule_lock, flags);
}