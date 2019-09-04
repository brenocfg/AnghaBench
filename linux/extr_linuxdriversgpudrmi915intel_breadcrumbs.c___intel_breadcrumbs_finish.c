#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_wait {TYPE_1__* tsk; int /*<<< orphan*/  node; } ;
struct intel_breadcrumbs {int /*<<< orphan*/  waiters; struct intel_wait* irq_wait; int /*<<< orphan*/  rb_lock; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ TASK_RUNNING ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (TYPE_1__*) ; 

__attribute__((used)) static inline void __intel_breadcrumbs_finish(struct intel_breadcrumbs *b,
					      struct intel_wait *wait)
{
	lockdep_assert_held(&b->rb_lock);
	GEM_BUG_ON(b->irq_wait == wait);

	/*
	 * This request is completed, so remove it from the tree, mark it as
	 * complete, and *then* wake up the associated task. N.B. when the
	 * task wakes up, it will find the empty rb_node, discern that it
	 * has already been removed from the tree and skip the serialisation
	 * of the b->rb_lock and b->irq_lock. This means that the destruction
	 * of the intel_wait is not serialised with the interrupt handler
	 * by the waiter - it must instead be serialised by the caller.
	 */
	rb_erase(&wait->node, &b->waiters);
	RB_CLEAR_NODE(&wait->node);

	if (wait->tsk->state != TASK_RUNNING)
		wake_up_process(wait->tsk); /* implicit smp_wmb() */
}