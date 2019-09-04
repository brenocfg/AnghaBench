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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ timeline; } ;
struct i915_sched_node {int dummy; } ;
struct TYPE_4__ {struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 TYPE_2__* sched_to_request (struct i915_sched_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct intel_engine_cs *
sched_lock_engine(struct i915_sched_node *node, struct intel_engine_cs *locked)
{
	struct intel_engine_cs *engine = sched_to_request(node)->engine;

	GEM_BUG_ON(!locked);

	if (engine != locked) {
		spin_unlock(&locked->timeline.lock);
		spin_lock(&engine->timeline.lock);
	}

	return engine;
}