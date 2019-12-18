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
typedef  int /*<<< orphan*/  u16 ;
struct i915_request {int dummy; } ;
struct drm_i915_mocs_table {int size; int n_entries; TYPE_1__* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  l3cc_value; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ GEM_WARN_ON (int) ; 
 int /*<<< orphan*/  GEN9_LNCFCMOCS (unsigned int) ; 
 size_t I915_MOCS_PTE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_entry_l3cc (struct drm_i915_mocs_table const*,int) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 void* l3cc_combine (struct drm_i915_mocs_table const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emit_mocs_l3cc_table(struct i915_request *rq,
				const struct drm_i915_mocs_table *table)
{
	u16 unused_value;
	unsigned int i;
	u32 *cs;

	if (GEM_WARN_ON(table->size > table->n_entries))
		return -ENODEV;

	/* Set unused values to PTE */
	unused_value = table->table[I915_MOCS_PTE].l3cc_value;

	cs = intel_ring_begin(rq, 2 + table->n_entries);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(table->n_entries / 2);

	for (i = 0; i < table->size / 2; i++) {
		u16 low = get_entry_l3cc(table, 2 * i);
		u16 high = get_entry_l3cc(table, 2 * i + 1);

		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(i));
		*cs++ = l3cc_combine(table, low, high);
	}

	/* Odd table size - 1 left over */
	if (table->size & 0x01) {
		u16 low = get_entry_l3cc(table, 2 * i);

		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(i));
		*cs++ = l3cc_combine(table, low, unused_value);
		i++;
	}

	/* All remaining entries are also unused */
	for (; i < table->n_entries / 2; i++) {
		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(i));
		*cs++ = l3cc_combine(table, unused_value, unused_value);
	}

	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}