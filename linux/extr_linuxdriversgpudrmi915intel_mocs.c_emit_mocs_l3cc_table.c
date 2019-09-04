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
struct i915_request {int dummy; } ;
struct drm_i915_mocs_table {int size; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GEN9_LNCFCMOCS (unsigned int) ; 
 int GEN9_NUM_MOCS_ENTRIES ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 void* l3cc_combine (struct drm_i915_mocs_table const*,int,int) ; 

__attribute__((used)) static int emit_mocs_l3cc_table(struct i915_request *rq,
				const struct drm_i915_mocs_table *table)
{
	unsigned int i;
	u32 *cs;

	if (WARN_ON(table->size > GEN9_NUM_MOCS_ENTRIES))
		return -ENODEV;

	cs = intel_ring_begin(rq, 2 + GEN9_NUM_MOCS_ENTRIES);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(GEN9_NUM_MOCS_ENTRIES / 2);

	for (i = 0; i < table->size/2; i++) {
		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(i));
		*cs++ = l3cc_combine(table, 2 * i, 2 * i + 1);
	}

	if (table->size & 0x01) {
		/* Odd table size - 1 left over */
		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(i));
		*cs++ = l3cc_combine(table, 2 * i, 0);
		i++;
	}

	/*
	 * Now set the rest of the table to uncached - use entry 0 as
	 * this will be uncached. Leave the last pair uninitialised as
	 * they are reserved by the hardware.
	 */
	for (; i < GEN9_NUM_MOCS_ENTRIES / 2; i++) {
		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(i));
		*cs++ = l3cc_combine(table, 0, 0);
	}

	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}