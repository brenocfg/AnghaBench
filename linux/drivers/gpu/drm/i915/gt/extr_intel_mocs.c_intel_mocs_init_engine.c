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
typedef  int /*<<< orphan*/  u32 ;
struct intel_uncore {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  i915; struct intel_uncore* uncore; } ;
struct intel_engine_cs {int /*<<< orphan*/  id; struct intel_gt* gt; } ;
struct drm_i915_mocs_table {unsigned int size; unsigned int n_entries; TYPE_1__* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 scalar_t__ HAS_GLOBAL_MOCS_REGISTERS (int /*<<< orphan*/ ) ; 
 size_t I915_MOCS_PTE ; 
 int /*<<< orphan*/  assert_forcewakes_active (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_entry_control (struct drm_i915_mocs_table*,unsigned int) ; 
 int /*<<< orphan*/  get_mocs_settings (struct intel_gt*,struct drm_i915_mocs_table*) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mocs_register (int /*<<< orphan*/ ,unsigned int) ; 

void intel_mocs_init_engine(struct intel_engine_cs *engine)
{
	struct intel_gt *gt = engine->gt;
	struct intel_uncore *uncore = gt->uncore;
	struct drm_i915_mocs_table table;
	unsigned int index;
	u32 unused_value;

	/* Platforms with global MOCS do not need per-engine initialization. */
	if (HAS_GLOBAL_MOCS_REGISTERS(gt->i915))
		return;

	/* Called under a blanket forcewake */
	assert_forcewakes_active(uncore, FORCEWAKE_ALL);

	if (!get_mocs_settings(gt, &table))
		return;

	/* Set unused values to PTE */
	unused_value = table.table[I915_MOCS_PTE].control_value;

	for (index = 0; index < table.size; index++) {
		u32 value = get_entry_control(&table, index);

		intel_uncore_write_fw(uncore,
				      mocs_register(engine->id, index),
				      value);
	}

	/* All remaining entries are also unused */
	for (; index < table.n_entries; index++)
		intel_uncore_write_fw(uncore,
				      mocs_register(engine->id, index),
				      unused_value);
}