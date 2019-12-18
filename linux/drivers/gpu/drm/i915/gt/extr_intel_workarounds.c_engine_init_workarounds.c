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
struct intel_engine_cs {scalar_t__ class; int /*<<< orphan*/  i915; } ;
struct i915_wa_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ I915_SELFTEST_ONLY (int) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RENDER_CLASS ; 
 int /*<<< orphan*/  rcs_engine_wa_init (struct intel_engine_cs*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  xcs_engine_wa_init (struct intel_engine_cs*,struct i915_wa_list*) ; 

__attribute__((used)) static void
engine_init_workarounds(struct intel_engine_cs *engine, struct i915_wa_list *wal)
{
	if (I915_SELFTEST_ONLY(INTEL_GEN(engine->i915) < 8))
		return;

	if (engine->class == RENDER_CLASS)
		rcs_engine_wa_init(engine, wal);
	else
		xcs_engine_wa_init(engine, wal);
}