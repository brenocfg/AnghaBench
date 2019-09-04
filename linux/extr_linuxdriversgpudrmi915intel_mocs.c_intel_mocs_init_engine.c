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
struct intel_engine_cs {int /*<<< orphan*/  id; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_mocs_table {unsigned int size; TYPE_1__* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_value; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int GEN9_NUM_MOCS_ENTRIES ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  get_mocs_settings (struct drm_i915_private*,struct drm_i915_mocs_table*) ; 
 int /*<<< orphan*/  mocs_register (int /*<<< orphan*/ ,unsigned int) ; 

int intel_mocs_init_engine(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	struct drm_i915_mocs_table table;
	unsigned int index;

	if (!get_mocs_settings(dev_priv, &table))
		return 0;

	if (WARN_ON(table.size > GEN9_NUM_MOCS_ENTRIES))
		return -ENODEV;

	for (index = 0; index < table.size; index++)
		I915_WRITE(mocs_register(engine->id, index),
			   table.table[index].control_value);

	/*
	 * Ok, now set the unused entries to uncached. These entries
	 * are officially undefined and no contract for the contents
	 * and settings is given for these entries.
	 *
	 * Entry 0 in the table is uncached - so we are just writing
	 * that value to all the used entries.
	 */
	for (; index < GEN9_NUM_MOCS_ENTRIES; index++)
		I915_WRITE(mocs_register(engine->id, index),
			   table.table[0].control_value);

	return 0;
}