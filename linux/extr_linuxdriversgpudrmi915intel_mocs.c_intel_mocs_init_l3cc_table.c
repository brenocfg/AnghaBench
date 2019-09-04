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
struct drm_i915_private {int dummy; } ;
struct drm_i915_mocs_table {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN9_LNCFCMOCS (unsigned int) ; 
 int GEN9_NUM_MOCS_ENTRIES ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mocs_settings (struct drm_i915_private*,struct drm_i915_mocs_table*) ; 
 int /*<<< orphan*/  l3cc_combine (struct drm_i915_mocs_table*,int,int) ; 

void intel_mocs_init_l3cc_table(struct drm_i915_private *dev_priv)
{
	struct drm_i915_mocs_table table;
	unsigned int i;

	if (!get_mocs_settings(dev_priv, &table))
		return;

	for (i = 0; i < table.size/2; i++)
		I915_WRITE(GEN9_LNCFCMOCS(i), l3cc_combine(&table, 2*i, 2*i+1));

	/* Odd table size - 1 left over */
	if (table.size & 0x01) {
		I915_WRITE(GEN9_LNCFCMOCS(i), l3cc_combine(&table, 2*i, 0));
		i++;
	}

	/*
	 * Now set the rest of the table to uncached - use entry 0 as
	 * this will be uncached. Leave the last pair as initialised as
	 * they are reserved by the hardware.
	 */
	for (; i < (GEN9_NUM_MOCS_ENTRIES / 2); i++)
		I915_WRITE(GEN9_LNCFCMOCS(i), l3cc_combine(&table, 0, 0));
}