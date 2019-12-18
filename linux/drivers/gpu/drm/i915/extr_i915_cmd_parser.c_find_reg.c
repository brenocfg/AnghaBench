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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {int reg_table_count; struct drm_i915_reg_table* reg_tables; } ;
struct drm_i915_reg_table {int /*<<< orphan*/  num_regs; int /*<<< orphan*/  regs; } ;
struct drm_i915_reg_descriptor {int dummy; } ;

/* Variables and functions */
 struct drm_i915_reg_descriptor* __find_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct drm_i915_reg_descriptor *
find_reg(const struct intel_engine_cs *engine, u32 addr)
{
	const struct drm_i915_reg_table *table = engine->reg_tables;
	const struct drm_i915_reg_descriptor *reg = NULL;
	int count = engine->reg_table_count;

	for (; !reg && (count > 0); ++table, --count)
		reg = __find_reg(table->regs, table->num_regs, addr);

	return reg;
}