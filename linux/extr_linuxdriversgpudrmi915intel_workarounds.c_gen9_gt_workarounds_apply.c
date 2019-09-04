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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int BDW_DISABLE_HDC_INVALIDATION ; 
 int /*<<< orphan*/  BDW_SCRATCH1 ; 
 int ECOCHK_DIS_TLB ; 
 int /*<<< orphan*/  GAM_ECOCHK ; 
 int /*<<< orphan*/  GEN7_FF_SLICE_CS_CHICKEN1 ; 
 int /*<<< orphan*/  GEN8_L3SQCREG1 ; 
 int /*<<< orphan*/  GEN8_L3SQCREG4 ; 
 int GEN8_LQSC_FLUSH_COHERENT_LINES ; 
 int /*<<< orphan*/  GEN9_CSFE_CHICKEN1_RCS ; 
 int /*<<< orphan*/  GEN9_FFSC_PERCTX_PREEMPT_CTRL ; 
 int GEN9_LBS_SLA_RETRY_TIMER_DECREMENT_ENABLE ; 
 int /*<<< orphan*/  GEN9_PREEMPT_GPGPU_SYNC_SWITCH_DISABLE ; 
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int L3_GENERAL_PRIO_CREDITS (int) ; 
 int L3_HIGH_PRIO_CREDITS (int) ; 
 int L3_PRIO_CREDITS_MASK ; 
 int MMCD_HOTSPOT_EN ; 
 int /*<<< orphan*/  MMCD_MISC_CTRL ; 
 int MMCD_PCLA ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen9_gt_workarounds_apply(struct drm_i915_private *dev_priv)
{
	/* WaContextSwitchWithConcurrentTLBInvalidate:skl,bxt,kbl,glk,cfl */
	I915_WRITE(GEN9_CSFE_CHICKEN1_RCS,
		   _MASKED_BIT_ENABLE(GEN9_PREEMPT_GPGPU_SYNC_SWITCH_DISABLE));

	/* WaEnableLbsSlaRetryTimerDecrement:skl,bxt,kbl,glk,cfl */
	I915_WRITE(BDW_SCRATCH1, I915_READ(BDW_SCRATCH1) |
		   GEN9_LBS_SLA_RETRY_TIMER_DECREMENT_ENABLE);

	/* WaDisableKillLogic:bxt,skl,kbl */
	if (!IS_COFFEELAKE(dev_priv))
		I915_WRITE(GAM_ECOCHK, I915_READ(GAM_ECOCHK) |
			   ECOCHK_DIS_TLB);

	if (HAS_LLC(dev_priv)) {
		/* WaCompressedResourceSamplerPbeMediaNewHashMode:skl,kbl
		 *
		 * Must match Display Engine. See
		 * WaCompressedResourceDisplayNewHashMode.
		 */
		I915_WRITE(MMCD_MISC_CTRL,
			   I915_READ(MMCD_MISC_CTRL) |
			   MMCD_PCLA |
			   MMCD_HOTSPOT_EN);
	}

	/* WaDisableHDCInvalidation:skl,bxt,kbl,cfl */
	I915_WRITE(GAM_ECOCHK, I915_READ(GAM_ECOCHK) |
		   BDW_DISABLE_HDC_INVALIDATION);

	/* WaProgramL3SqcReg1DefaultForPerf:bxt,glk */
	if (IS_GEN9_LP(dev_priv)) {
		u32 val = I915_READ(GEN8_L3SQCREG1);

		val &= ~L3_PRIO_CREDITS_MASK;
		val |= L3_GENERAL_PRIO_CREDITS(62) | L3_HIGH_PRIO_CREDITS(2);
		I915_WRITE(GEN8_L3SQCREG1, val);
	}

	/* WaOCLCoherentLineFlush:skl,bxt,kbl,cfl */
	I915_WRITE(GEN8_L3SQCREG4,
		   I915_READ(GEN8_L3SQCREG4) | GEN8_LQSC_FLUSH_COHERENT_LINES);

	/* WaEnablePreemptionGranularityControlByUMD:skl,bxt,kbl,cfl,[cnl] */
	I915_WRITE(GEN7_FF_SLICE_CS_CHICKEN1,
		   _MASKED_BIT_ENABLE(GEN9_FFSC_PERCTX_PREEMPT_CTRL));
}