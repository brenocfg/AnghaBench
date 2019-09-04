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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ timeline; int /*<<< orphan*/  name; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELINE_ENGINE ; 
 int /*<<< orphan*/  i915_timeline_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_init_batch_pool (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_cmd_parser (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_execlist (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_hangcheck (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void intel_engine_setup_common(struct intel_engine_cs *engine)
{
	i915_timeline_init(engine->i915, &engine->timeline, engine->name);
	lockdep_set_subclass(&engine->timeline.lock, TIMELINE_ENGINE);

	intel_engine_init_execlist(engine);
	intel_engine_init_hangcheck(engine);
	intel_engine_init_batch_pool(engine);
	intel_engine_init_cmd_parser(engine);
}