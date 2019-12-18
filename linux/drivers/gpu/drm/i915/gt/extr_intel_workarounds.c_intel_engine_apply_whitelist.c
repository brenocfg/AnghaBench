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
struct intel_uncore {int dummy; } ;
struct i915_wa_list {unsigned int count; struct i915_wa* list; } ;
struct intel_engine_cs {int /*<<< orphan*/  mmio_base; struct intel_uncore* uncore; struct i915_wa_list whitelist; } ;
struct i915_wa {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_FORCE_TO_NONPRIV (int /*<<< orphan*/  const,unsigned int) ; 
 unsigned int RING_MAX_NONPRIV_SLOTS ; 
 int /*<<< orphan*/  RING_NOPID (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_engine_apply_whitelist(struct intel_engine_cs *engine)
{
	const struct i915_wa_list *wal = &engine->whitelist;
	struct intel_uncore *uncore = engine->uncore;
	const u32 base = engine->mmio_base;
	struct i915_wa *wa;
	unsigned int i;

	if (!wal->count)
		return;

	for (i = 0, wa = wal->list; i < wal->count; i++, wa++)
		intel_uncore_write(uncore,
				   RING_FORCE_TO_NONPRIV(base, i),
				   i915_mmio_reg_offset(wa->reg));

	/* And clear the rest just in case of garbage */
	for (; i < RING_MAX_NONPRIV_SLOTS; i++)
		intel_uncore_write(uncore,
				   RING_FORCE_TO_NONPRIV(base, i),
				   i915_mmio_reg_offset(RING_NOPID(base)));
}