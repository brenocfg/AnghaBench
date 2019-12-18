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
struct TYPE_2__ {int /*<<< orphan*/  priority; } ;
struct i915_sched_node {scalar_t__ flags; scalar_t__ semaphores; TYPE_1__ attr; int /*<<< orphan*/  link; int /*<<< orphan*/  waiters_list; int /*<<< orphan*/  signalers_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_PRIORITY_INVALID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void i915_sched_node_init(struct i915_sched_node *node)
{
	INIT_LIST_HEAD(&node->signalers_list);
	INIT_LIST_HEAD(&node->waiters_list);
	INIT_LIST_HEAD(&node->link);
	node->attr.priority = I915_PRIORITY_INVALID;
	node->semaphores = 0;
	node->flags = 0;
}