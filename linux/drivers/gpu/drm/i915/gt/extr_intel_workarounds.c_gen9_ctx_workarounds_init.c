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
 int /*<<< orphan*/  CACHE_MODE_1 ; 
 int /*<<< orphan*/  COMMON_SLICE_CHICKEN2 ; 
 int FLOW_CONTROL_ENABLE ; 
 int GEN8_4x4_STC_OPTIMIZATION_DISABLE ; 
 int /*<<< orphan*/  GEN8_CS_CHICKEN1 ; 
 int /*<<< orphan*/  GEN8_ROW_CHICKEN ; 
 int GEN8_SAMPLER_POWER_BYPASS_DIS ; 
 int GEN8_ST_PO_DISABLE ; 
 int /*<<< orphan*/  GEN9_CCS_TLB_PREFETCH_ENABLE ; 
 int GEN9_ENABLE_GPGPU_PREEMPTION ; 
 int GEN9_ENABLE_YV12_BUGFIX ; 
 int GEN9_FACTOR_IN_CLR_VAL_HIZ ; 
 int /*<<< orphan*/  GEN9_HALF_SLICE_CHICKEN5 ; 
 int /*<<< orphan*/  GEN9_HALF_SLICE_CHICKEN7 ; 
 int GEN9_PARTIAL_RESOLVE_IN_VC_DISABLE ; 
 int GEN9_PBE_COMPRESSED_HASH_SELECTION ; 
 int /*<<< orphan*/  GEN9_PREEMPT_3D_OBJECT_LEVEL ; 
 int /*<<< orphan*/  GEN9_PREEMPT_GPGPU_COMMAND_LEVEL ; 
 int /*<<< orphan*/  GEN9_PREEMPT_GPGPU_LEVEL_MASK ; 
 int GEN9_SAMPLER_HASH_COMPRESSED_READ_ADDR ; 
 int /*<<< orphan*/  GEN9_WM_CHICKEN3 ; 
 int /*<<< orphan*/  HALF_SLICE_CHICKEN2 ; 
 int /*<<< orphan*/  HALF_SLICE_CHICKEN3 ; 
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HDC_CHICKEN0 ; 
 int HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT ; 
 int HDC_FORCE_CSR_NON_COHERENT_OVR_DISABLE ; 
 int HDC_FORCE_NON_COHERENT ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int PARTIAL_INSTRUCTION_SHOOTDOWN_DISABLE ; 
 int /*<<< orphan*/  WA_CLR_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WA_SET_BIT_MASKED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WA_SET_FIELD_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen9_ctx_workarounds_init(struct intel_engine_cs *engine,
				      struct i915_wa_list *wal)
{
	struct drm_i915_private *i915 = engine->i915;

	if (HAS_LLC(i915)) {
		/* WaCompressedResourceSamplerPbeMediaNewHashMode:skl,kbl
		 *
		 * Must match Display Engine. See
		 * WaCompressedResourceDisplayNewHashMode.
		 */
		WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
				  GEN9_PBE_COMPRESSED_HASH_SELECTION);
		WA_SET_BIT_MASKED(GEN9_HALF_SLICE_CHICKEN7,
				  GEN9_SAMPLER_HASH_COMPRESSED_READ_ADDR);
	}

	/* WaClearFlowControlGpgpuContextSave:skl,bxt,kbl,glk,cfl */
	/* WaDisablePartialInstShootdown:skl,bxt,kbl,glk,cfl */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN,
			  FLOW_CONTROL_ENABLE |
			  PARTIAL_INSTRUCTION_SHOOTDOWN_DISABLE);

	/* WaEnableYV12BugFixInHalfSliceChicken7:skl,bxt,kbl,glk,cfl */
	/* WaEnableSamplerGPGPUPreemptionSupport:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(GEN9_HALF_SLICE_CHICKEN7,
			  GEN9_ENABLE_YV12_BUGFIX |
			  GEN9_ENABLE_GPGPU_PREEMPTION);

	/* Wa4x4STCOptimizationDisable:skl,bxt,kbl,glk,cfl */
	/* WaDisablePartialResolveInVc:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(CACHE_MODE_1,
			  GEN8_4x4_STC_OPTIMIZATION_DISABLE |
			  GEN9_PARTIAL_RESOLVE_IN_VC_DISABLE);

	/* WaCcsTlbPrefetchDisable:skl,bxt,kbl,glk,cfl */
	WA_CLR_BIT_MASKED(GEN9_HALF_SLICE_CHICKEN5,
			  GEN9_CCS_TLB_PREFETCH_ENABLE);

	/* WaForceContextSaveRestoreNonCoherent:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(HDC_CHICKEN0,
			  HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT |
			  HDC_FORCE_CSR_NON_COHERENT_OVR_DISABLE);

	/* WaForceEnableNonCoherent and WaDisableHDCInvalidation are
	 * both tied to WaForceContextSaveRestoreNonCoherent
	 * in some hsds for skl. We keep the tie for all gen9. The
	 * documentation is a bit hazy and so we want to get common behaviour,
	 * even though there is no clear evidence we would need both on kbl/bxt.
	 * This area has been source of system hangs so we play it safe
	 * and mimic the skl regardless of what bspec says.
	 *
	 * Use Force Non-Coherent whenever executing a 3D context. This
	 * is a workaround for a possible hang in the unlikely event
	 * a TLB invalidation occurs during a PSD flush.
	 */

	/* WaForceEnableNonCoherent:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(HDC_CHICKEN0,
			  HDC_FORCE_NON_COHERENT);

	/* WaDisableSamplerPowerBypassForSOPingPong:skl,bxt,kbl,cfl */
	if (IS_SKYLAKE(i915) || IS_KABYLAKE(i915) || IS_COFFEELAKE(i915))
		WA_SET_BIT_MASKED(HALF_SLICE_CHICKEN3,
				  GEN8_SAMPLER_POWER_BYPASS_DIS);

	/* WaDisableSTUnitPowerOptimization:skl,bxt,kbl,glk,cfl */
	WA_SET_BIT_MASKED(HALF_SLICE_CHICKEN2, GEN8_ST_PO_DISABLE);

	/*
	 * Supporting preemption with fine-granularity requires changes in the
	 * batch buffer programming. Since we can't break old userspace, we
	 * need to set our default preemption level to safe value. Userspace is
	 * still able to use more fine-grained preemption levels, since in
	 * WaEnablePreemptionGranularityControlByUMD we're whitelisting the
	 * per-ctx register. As such, WaDisable{3D,GPGPU}MidCmdPreemption are
	 * not real HW workarounds, but merely a way to start using preemption
	 * while maintaining old contract with userspace.
	 */

	/* WaDisable3DMidCmdPreemption:skl,bxt,glk,cfl,[cnl] */
	WA_CLR_BIT_MASKED(GEN8_CS_CHICKEN1, GEN9_PREEMPT_3D_OBJECT_LEVEL);

	/* WaDisableGPGPUMidCmdPreemption:skl,bxt,blk,cfl,[cnl] */
	WA_SET_FIELD_MASKED(GEN8_CS_CHICKEN1,
			    GEN9_PREEMPT_GPGPU_LEVEL_MASK,
			    GEN9_PREEMPT_GPGPU_COMMAND_LEVEL);

	/* WaClearHIZ_WM_CHICKEN3:bxt,glk */
	if (IS_GEN9_LP(i915))
		WA_SET_BIT_MASKED(GEN9_WM_CHICKEN3, GEN9_FACTOR_IN_CLR_VAL_HIZ);
}