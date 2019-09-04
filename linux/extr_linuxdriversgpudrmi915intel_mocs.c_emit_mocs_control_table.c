#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {TYPE_1__* engine; } ;
struct drm_i915_mocs_table {int size; TYPE_2__* table; } ;
typedef  enum intel_engine_id { ____Placeholder_intel_engine_id } intel_engine_id ;
struct TYPE_4__ {int /*<<< orphan*/  control_value; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int ENODEV ; 
 int GEN9_NUM_MOCS_ENTRIES ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int /*<<< orphan*/  mocs_register (int,unsigned int) ; 

__attribute__((used)) static int emit_mocs_control_table(struct i915_request *rq,
				   const struct drm_i915_mocs_table *table)
{
	enum intel_engine_id engine = rq->engine->id;
	unsigned int index;
	u32 *cs;

	if (WARN_ON(table->size > GEN9_NUM_MOCS_ENTRIES))
		return -ENODEV;

	cs = intel_ring_begin(rq, 2 + 2 * GEN9_NUM_MOCS_ENTRIES);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(GEN9_NUM_MOCS_ENTRIES);

	for (index = 0; index < table->size; index++) {
		*cs++ = i915_mmio_reg_offset(mocs_register(engine, index));
		*cs++ = table->table[index].control_value;
	}

	/*
	 * Ok, now set the unused entries to uncached. These entries
	 * are officially undefined and no contract for the contents
	 * and settings is given for these entries.
	 *
	 * Entry 0 in the table is uncached - so we are just writing
	 * that value to all the used entries.
	 */
	for (; index < GEN9_NUM_MOCS_ENTRIES; index++) {
		*cs++ = i915_mmio_reg_offset(mocs_register(engine, index));
		*cs++ = table->table[0].control_value;
	}

	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}