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
struct intel_engine_cs {struct drm_i915_private* i915; } ;
struct i915_wa_list {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_FAST_ANISO_L1_BANKING_FIX ; 
 int /*<<< orphan*/  CNL_HDC_CHICKEN0 ; 
 int /*<<< orphan*/  CNL_REVID_B0 ; 
 int /*<<< orphan*/  COMMON_SLICE_CHICKEN2 ; 
 int /*<<< orphan*/  DISABLE_EARLY_EOT ; 
 int /*<<< orphan*/  GEN7_ROW_CHICKEN2 ; 
 int /*<<< orphan*/  GEN8_CSC2_SBE_VUE_CACHE_CONSERVATIVE ; 
 int /*<<< orphan*/  GEN8_CS_CHICKEN1 ; 
 int /*<<< orphan*/  GEN8_ROW_CHICKEN ; 
 int /*<<< orphan*/  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION ; 
 int /*<<< orphan*/  GEN9_PREEMPT_3D_OBJECT_LEVEL ; 
 int /*<<< orphan*/  GEN9_PREEMPT_GPGPU_COMMAND_LEVEL ; 
 int /*<<< orphan*/  GEN9_PREEMPT_GPGPU_LEVEL_MASK ; 
 int /*<<< orphan*/  HALF_SLICE_CHICKEN3 ; 
 int /*<<< orphan*/  HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT ; 
 scalar_t__ IS_CNL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSH_CONSTANT_DEREF_DISABLE ; 
 int /*<<< orphan*/  THROTTLE_12_5 ; 
 int /*<<< orphan*/  WA_CLR_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WA_SET_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WA_SET_FIELD_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnl_ctx_workarounds_init(struct intel_engine_cs *engine,
				     struct i915_wa_list *wal)
{
	struct drm_i915_private *i915 = engine->i915;

	/* WaForceContextSaveRestoreNonCoherent:cnl */
	WA_SET_BIT_MASKED(CNL_HDC_CHICKEN0,
			  HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT);

	/* WaThrottleEUPerfToAvoidTDBackPressure:cnl(pre-prod) */
	if (IS_CNL_REVID(i915, CNL_REVID_B0, CNL_REVID_B0))
		WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN, THROTTLE_12_5);

	/* WaDisableReplayBufferBankArbitrationOptimization:cnl */
	WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
			  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaDisableEnhancedSBEVertexCaching:cnl (pre-prod) */
	if (IS_CNL_REVID(i915, 0, CNL_REVID_B0))
		WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
				  GEN8_CSC2_SBE_VUE_CACHE_CONSERVATIVE);

	/* WaPushConstantDereferenceHoldDisable:cnl */
	WA_SET_BIT_MASKED(GEN7_ROW_CHICKEN2, PUSH_CONSTANT_DEREF_DISABLE);

	/* FtrEnableFastAnisoL1BankingFix:cnl */
	WA_SET_BIT_MASKED(HALF_SLICE_CHICKEN3, CNL_FAST_ANISO_L1_BANKING_FIX);

	/* WaDisable3DMidCmdPreemption:cnl */
	WA_CLR_BIT_MASKED(GEN8_CS_CHICKEN1, GEN9_PREEMPT_3D_OBJECT_LEVEL);

	/* WaDisableGPGPUMidCmdPreemption:cnl */
	WA_SET_FIELD_MASKED(GEN8_CS_CHICKEN1,
			    GEN9_PREEMPT_GPGPU_LEVEL_MASK,
			    GEN9_PREEMPT_GPGPU_COMMAND_LEVEL);

	/* WaDisableEarlyEOT:cnl */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN, DISABLE_EARLY_EOT);
}