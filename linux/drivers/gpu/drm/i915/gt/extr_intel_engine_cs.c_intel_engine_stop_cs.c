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
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  i915; int /*<<< orphan*/  mmio_base; struct intel_uncore* uncore; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE_IDLE ; 
 int /*<<< orphan*/  RING_MI_MODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  STOP_RING ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ __intel_wait_for_register_fw (struct intel_uncore*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_posting_read_fw (struct intel_uncore*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

int intel_engine_stop_cs(struct intel_engine_cs *engine)
{
	struct intel_uncore *uncore = engine->uncore;
	const u32 base = engine->mmio_base;
	const i915_reg_t mode = RING_MI_MODE(base);
	int err;

	if (INTEL_GEN(engine->i915) < 3)
		return -ENODEV;

	GEM_TRACE("%s\n", engine->name);

	intel_uncore_write_fw(uncore, mode, _MASKED_BIT_ENABLE(STOP_RING));

	err = 0;
	if (__intel_wait_for_register_fw(uncore,
					 mode, MODE_IDLE, MODE_IDLE,
					 1000, 0,
					 NULL)) {
		GEM_TRACE("%s: timed out on STOP_RING -> IDLE\n", engine->name);
		err = -ETIMEDOUT;
	}

	/* A final mmio read to let GPU writes be hopefully flushed to memory */
	intel_uncore_posting_read_fw(uncore, mode);

	return err;
}