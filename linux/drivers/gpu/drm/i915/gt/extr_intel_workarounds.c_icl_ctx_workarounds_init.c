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
struct intel_engine_cs {int /*<<< orphan*/  uncore; struct drm_i915_private* i915; } ;
struct i915_wa_list {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOAT_BLEND_OPTIMIZATION_ENABLE ; 
 int /*<<< orphan*/  GEN10_CACHE_MODE_SS ; 
 int /*<<< orphan*/  GEN10_SAMPLER_MODE ; 
 int /*<<< orphan*/  GEN11_BLEND_EMB_FIX_DISABLE_IN_RCC ; 
 int /*<<< orphan*/  GEN11_COMMON_SLICE_CHICKEN3 ; 
 int /*<<< orphan*/  GEN11_SAMPLER_ENABLE_HEADLESS_MSG ; 
 int /*<<< orphan*/  GEN11_TDL_CLOCK_GATING_FIX_DISABLE ; 
 int /*<<< orphan*/  GEN7_ROW_CHICKEN2 ; 
 int /*<<< orphan*/  GEN8_CS_CHICKEN1 ; 
 int GEN8_ERRDETBCTRL ; 
 int /*<<< orphan*/  GEN8_L3CNTLREG ; 
 int /*<<< orphan*/  GEN9_PREEMPT_GPGPU_LEVEL_MASK ; 
 int /*<<< orphan*/  GEN9_PREEMPT_GPGPU_THREAD_GROUP_LEVEL ; 
 int /*<<< orphan*/  HDC_FORCE_NON_COHERENT ; 
 int /*<<< orphan*/  ICL_HDC_MODE ; 
 int /*<<< orphan*/  ICL_REVID_A0 ; 
 int /*<<< orphan*/  ICL_REVID_B0 ; 
 scalar_t__ IS_ICL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSH_CONSTANT_DEREF_DISABLE ; 
 int /*<<< orphan*/  WA_SET_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WA_SET_FIELD_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int intel_uncore_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_write (struct i915_wa_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wa_write_masked_or (struct i915_wa_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_ctx_workarounds_init(struct intel_engine_cs *engine,
				     struct i915_wa_list *wal)
{
	struct drm_i915_private *i915 = engine->i915;

	/* WaDisableBankHangMode:icl */
	wa_write(wal,
		 GEN8_L3CNTLREG,
		 intel_uncore_read(engine->uncore, GEN8_L3CNTLREG) |
		 GEN8_ERRDETBCTRL);

	/* Wa_1604370585:icl (pre-prod)
	 * Formerly known as WaPushConstantDereferenceHoldDisable
	 */
	if (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_B0))
		WA_SET_BIT_MASKED(GEN7_ROW_CHICKEN2,
				  PUSH_CONSTANT_DEREF_DISABLE);

	/* WaForceEnableNonCoherent:icl
	 * This is not the same workaround as in early Gen9 platforms, where
	 * lacking this could cause system hangs, but coherency performance
	 * overhead is high and only a few compute workloads really need it
	 * (the register is whitelisted in hardware now, so UMDs can opt in
	 * for coherency if they have a good reason).
	 */
	WA_SET_BIT_MASKED(ICL_HDC_MODE, HDC_FORCE_NON_COHERENT);

	/* Wa_2006611047:icl (pre-prod)
	 * Formerly known as WaDisableImprovedTdlClkGating
	 */
	if (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_A0))
		WA_SET_BIT_MASKED(GEN7_ROW_CHICKEN2,
				  GEN11_TDL_CLOCK_GATING_FIX_DISABLE);

	/* Wa_2006665173:icl (pre-prod) */
	if (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_A0))
		WA_SET_BIT_MASKED(GEN11_COMMON_SLICE_CHICKEN3,
				  GEN11_BLEND_EMB_FIX_DISABLE_IN_RCC);

	/* WaEnableFloatBlendOptimization:icl */
	wa_write_masked_or(wal,
			   GEN10_CACHE_MODE_SS,
			   0, /* write-only, so skip validation */
			   _MASKED_BIT_ENABLE(FLOAT_BLEND_OPTIMIZATION_ENABLE));

	/* WaDisableGPGPUMidThreadPreemption:icl */
	WA_SET_FIELD_MASKED(GEN8_CS_CHICKEN1,
			    GEN9_PREEMPT_GPGPU_LEVEL_MASK,
			    GEN9_PREEMPT_GPGPU_THREAD_GROUP_LEVEL);

	/* allow headerless messages for preemptible GPGPU context */
	WA_SET_BIT_MASKED(GEN10_SAMPLER_MODE,
			  GEN11_SAMPLER_ENABLE_HEADLESS_MSG);
}