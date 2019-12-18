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
struct intel_engine_cs {int dummy; } ;
struct i915_wa_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_SLICE_CHICKEN2 ; 
 int /*<<< orphan*/  GEN8_ROW_CHICKEN ; 
 int /*<<< orphan*/  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION ; 
 int /*<<< orphan*/  STALL_DOP_GATING_DISABLE ; 
 int /*<<< orphan*/  WA_SET_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen9_ctx_workarounds_init (struct intel_engine_cs*,struct i915_wa_list*) ; 

__attribute__((used)) static void bxt_ctx_workarounds_init(struct intel_engine_cs *engine,
				     struct i915_wa_list *wal)
{
	gen9_ctx_workarounds_init(engine, wal);

	/* WaDisableThreadStallDopClockGating:bxt */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN,
			  STALL_DOP_GATING_DISABLE);

	/* WaToEnableHwFixForPushConstHWBug:bxt */
	WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
			  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);
}