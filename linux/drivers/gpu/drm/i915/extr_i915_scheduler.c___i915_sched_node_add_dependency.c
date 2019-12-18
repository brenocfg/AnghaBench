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
struct i915_sched_node {int flags; int /*<<< orphan*/  signalers_list; int /*<<< orphan*/  waiters_list; } ;
struct i915_dependency {unsigned long flags; struct i915_sched_node* waiter; struct i915_sched_node* signaler; int /*<<< orphan*/  signal_link; int /*<<< orphan*/  wait_link; int /*<<< orphan*/  dfs_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned long I915_DEPENDENCY_EXTERNAL ; 
 int I915_PRIORITY_MASK ; 
 int I915_SCHED_HAS_SEMAPHORE_CHAIN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __NO_PREEMPTION ; 
 int /*<<< orphan*/  __bump_priority (struct i915_sched_node*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_signaled (struct i915_sched_node*) ; 
 int /*<<< orphan*/  node_started (struct i915_sched_node*) ; 
 int /*<<< orphan*/  schedule_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool __i915_sched_node_add_dependency(struct i915_sched_node *node,
				      struct i915_sched_node *signal,
				      struct i915_dependency *dep,
				      unsigned long flags)
{
	bool ret = false;

	spin_lock_irq(&schedule_lock);

	if (!node_signaled(signal)) {
		INIT_LIST_HEAD(&dep->dfs_link);
		list_add(&dep->wait_link, &signal->waiters_list);
		list_add(&dep->signal_link, &node->signalers_list);
		dep->signaler = signal;
		dep->waiter = node;
		dep->flags = flags;

		/* Keep track of whether anyone on this chain has a semaphore */
		if (signal->flags & I915_SCHED_HAS_SEMAPHORE_CHAIN &&
		    !node_started(signal))
			node->flags |= I915_SCHED_HAS_SEMAPHORE_CHAIN;

		/*
		 * As we do not allow WAIT to preempt inflight requests,
		 * once we have executed a request, along with triggering
		 * any execution callbacks, we must preserve its ordering
		 * within the non-preemptible FIFO.
		 */
		BUILD_BUG_ON(__NO_PREEMPTION & ~I915_PRIORITY_MASK);
		if (flags & I915_DEPENDENCY_EXTERNAL)
			__bump_priority(signal, __NO_PREEMPTION);

		ret = true;
	}

	spin_unlock_irq(&schedule_lock);

	return ret;
}