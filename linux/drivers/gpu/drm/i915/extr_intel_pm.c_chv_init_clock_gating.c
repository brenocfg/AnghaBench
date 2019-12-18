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

/* Variables and functions */
 int GEN6_CSUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  GEN6_RC_SLEEP_PSMI_CONTROL ; 
 int /*<<< orphan*/  GEN6_UCGCTL1 ; 
 int /*<<< orphan*/  GEN7_FF_THREAD_MODE ; 
 int GEN7_FF_VS_REF_CNT_FFME ; 
 int GEN8_FF_DS_REF_CNT_FFME ; 
 int /*<<< orphan*/  GEN8_RC_SEMA_IDLE_MSG_DISABLE ; 
 int GEN8_SDEUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  GEN8_UCGCTL6 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_set_l3sqc_credits (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static void chv_init_clock_gating(struct drm_i915_private *dev_priv)
{
	/* WaVSRefCountFullforceMissDisable:chv */
	/* WaDSRefCountFullforceMissDisable:chv */
	I915_WRITE(GEN7_FF_THREAD_MODE,
		   I915_READ(GEN7_FF_THREAD_MODE) &
		   ~(GEN8_FF_DS_REF_CNT_FFME | GEN7_FF_VS_REF_CNT_FFME));

	/* WaDisableSemaphoreAndSyncFlipWait:chv */
	I915_WRITE(GEN6_RC_SLEEP_PSMI_CONTROL,
		   _MASKED_BIT_ENABLE(GEN8_RC_SEMA_IDLE_MSG_DISABLE));

	/* WaDisableCSUnitClockGating:chv */
	I915_WRITE(GEN6_UCGCTL1, I915_READ(GEN6_UCGCTL1) |
		   GEN6_CSUNIT_CLOCK_GATE_DISABLE);

	/* WaDisableSDEUnitClockGating:chv */
	I915_WRITE(GEN8_UCGCTL6, I915_READ(GEN8_UCGCTL6) |
		   GEN8_SDEUNIT_CLOCK_GATE_DISABLE);

	/*
	 * WaProgramL3SqcReg1Default:chv
	 * See gfxspecs/Related Documents/Performance Guide/
	 * LSQC Setting Recommendations.
	 */
	gen8_set_l3sqc_credits(dev_priv, 38, 2);
}