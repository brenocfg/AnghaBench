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
struct i915_sched_node {int /*<<< orphan*/  signalers_list; int /*<<< orphan*/  waiters_list; } ;
struct i915_dependency {unsigned long flags; struct i915_sched_node* signaler; int /*<<< orphan*/  signal_link; int /*<<< orphan*/  wait_link; int /*<<< orphan*/  dfs_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__i915_sched_node_add_dependency(struct i915_sched_node *node,
				 struct i915_sched_node *signal,
				 struct i915_dependency *dep,
				 unsigned long flags)
{
	INIT_LIST_HEAD(&dep->dfs_link);
	list_add(&dep->wait_link, &signal->waiters_list);
	list_add(&dep->signal_link, &node->signalers_list);
	dep->signaler = signal;
	dep->flags = flags;
}