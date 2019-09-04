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
struct intel_engine_cs {int reg_table_count; struct drm_i915_reg_table* reg_tables; } ;
struct drm_i915_reg_table {int /*<<< orphan*/  num_regs; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_sorted (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool validate_regs_sorted(struct intel_engine_cs *engine)
{
	int i;
	const struct drm_i915_reg_table *table;

	for (i = 0; i < engine->reg_table_count; i++) {
		table = &engine->reg_tables[i];
		if (!check_sorted(engine, table->regs, table->num_regs))
			return false;
	}

	return true;
}