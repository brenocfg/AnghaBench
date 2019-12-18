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
typedef  int /*<<< orphan*/  u16 ;
struct intel_uncore {int dummy; } ;
struct intel_gt {struct intel_uncore* uncore; } ;
struct drm_i915_mocs_table {int size; int n_entries; TYPE_1__* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  l3cc_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN9_LNCFCMOCS (unsigned int) ; 
 size_t I915_MOCS_PTE ; 
 int /*<<< orphan*/  get_entry_l3cc (struct drm_i915_mocs_table*,int) ; 
 int /*<<< orphan*/  get_mocs_settings (struct intel_gt*,struct drm_i915_mocs_table*) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l3cc_combine (struct drm_i915_mocs_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_mocs_init_l3cc_table(struct intel_gt *gt)
{
	struct intel_uncore *uncore = gt->uncore;
	struct drm_i915_mocs_table table;
	unsigned int i;
	u16 unused_value;

	if (!get_mocs_settings(gt, &table))
		return;

	/* Set unused values to PTE */
	unused_value = table.table[I915_MOCS_PTE].l3cc_value;

	for (i = 0; i < table.size / 2; i++) {
		u16 low = get_entry_l3cc(&table, 2 * i);
		u16 high = get_entry_l3cc(&table, 2 * i + 1);

		intel_uncore_write(uncore,
				   GEN9_LNCFCMOCS(i),
				   l3cc_combine(&table, low, high));
	}

	/* Odd table size - 1 left over */
	if (table.size & 0x01) {
		u16 low = get_entry_l3cc(&table, 2 * i);

		intel_uncore_write(uncore,
				   GEN9_LNCFCMOCS(i),
				   l3cc_combine(&table, low, unused_value));
		i++;
	}

	/* All remaining entries are also unused */
	for (; i < table.n_entries / 2; i++)
		intel_uncore_write(uncore,
				   GEN9_LNCFCMOCS(i),
				   l3cc_combine(&table, unused_value,
						unused_value));
}