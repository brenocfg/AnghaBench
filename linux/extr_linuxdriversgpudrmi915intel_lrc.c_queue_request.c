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
struct intel_engine_cs {int dummy; } ;
struct i915_sched_node {int /*<<< orphan*/  link; } ;
struct TYPE_2__ {int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookup_priolist (struct intel_engine_cs*,int) ; 

__attribute__((used)) static void queue_request(struct intel_engine_cs *engine,
			  struct i915_sched_node *node,
			  int prio)
{
	list_add_tail(&node->link,
		      &lookup_priolist(engine, prio)->requests);
}