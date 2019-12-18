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
struct i915_wa_list {int dummy; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  i915; struct i915_wa_list wa_list; } ;

/* Variables and functions */
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_init_workarounds (struct intel_engine_cs*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  wa_init_finish (struct i915_wa_list*) ; 
 int /*<<< orphan*/  wa_init_start (struct i915_wa_list*,char*,int /*<<< orphan*/ ) ; 

void intel_engine_init_workarounds(struct intel_engine_cs *engine)
{
	struct i915_wa_list *wal = &engine->wa_list;

	if (INTEL_GEN(engine->i915) < 8)
		return;

	wa_init_start(wal, "engine", engine->name);
	engine_init_workarounds(engine, wal);
	wa_init_finish(wal);
}