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
 int /*<<< orphan*/  GEN11_BLEND_EMB_FIX_DISABLE_IN_RCC ; 
 int /*<<< orphan*/  GEN11_COMMON_SLICE_CHICKEN3 ; 
 int /*<<< orphan*/  GEN11_STATE_CACHE_REDIRECT_TO_CS ; 
 int /*<<< orphan*/  GEN11_TDL_CLOCK_GATING_FIX_DISABLE ; 
 int /*<<< orphan*/  GEN7_ROW_CHICKEN2 ; 
 int /*<<< orphan*/  GEN9_SLICE_COMMON_ECO_CHICKEN1 ; 
 int /*<<< orphan*/  HDC_FORCE_NON_COHERENT ; 
 int /*<<< orphan*/  ICL_HDC_MODE ; 
 int /*<<< orphan*/  ICL_REVID_A0 ; 
 int /*<<< orphan*/  ICL_REVID_B0 ; 
 scalar_t__ IS_ICL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSH_CONSTANT_DEREF_DISABLE ; 
 int /*<<< orphan*/  WA_SET_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icl_ctx_workarounds_init(struct drm_i915_private *dev_priv)
{
	/* Wa_1604370585:icl (pre-prod)
	 * Formerly known as WaPushConstantDereferenceHoldDisable
	 */
	if (IS_ICL_REVID(dev_priv, ICL_REVID_A0, ICL_REVID_B0))
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
	if (IS_ICL_REVID(dev_priv, ICL_REVID_A0, ICL_REVID_A0))
		WA_SET_BIT_MASKED(GEN7_ROW_CHICKEN2,
				  GEN11_TDL_CLOCK_GATING_FIX_DISABLE);

	/* WaEnableStateCacheRedirectToCS:icl */
	WA_SET_BIT_MASKED(GEN9_SLICE_COMMON_ECO_CHICKEN1,
			  GEN11_STATE_CACHE_REDIRECT_TO_CS);

	/* Wa_2006665173:icl (pre-prod) */
	if (IS_ICL_REVID(dev_priv, ICL_REVID_A0, ICL_REVID_A0))
		WA_SET_BIT_MASKED(GEN11_COMMON_SLICE_CHICKEN3,
				  GEN11_BLEND_EMB_FIX_DISABLE_IN_RCC);

	return 0;
}