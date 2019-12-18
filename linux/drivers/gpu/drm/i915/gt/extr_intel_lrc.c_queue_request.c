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
struct intel_engine_cs {int dummy; } ;
struct i915_sched_node {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_sched_lookup_priolist (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_request(struct intel_engine_cs *engine,
			  struct i915_sched_node *node,
			  int prio)
{
	GEM_BUG_ON(!list_empty(&node->link));
	list_add_tail(&node->link, i915_sched_lookup_priolist(engine, prio));
}