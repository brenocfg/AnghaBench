#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  DPLL_ID_ICL_DPLL0 134 
#define  DPLL_ID_ICL_DPLL1 133 
#define  DPLL_ID_ICL_MGPLL1 132 
#define  DPLL_ID_ICL_MGPLL2 131 
#define  DPLL_ID_ICL_MGPLL3 130 
#define  DPLL_ID_ICL_MGPLL4 129 
#define  DPLL_ID_ICL_TBTPLL 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int const) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int const) ; 
 int /*<<< orphan*/  PLL_ENABLE ; 
 int /*<<< orphan*/  PLL_LOCK ; 
 int /*<<< orphan*/  PLL_POWER_ENABLE ; 
 int /*<<< orphan*/  PLL_POWER_STATE ; 
 int /*<<< orphan*/  icl_dpll_write (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 int /*<<< orphan*/  icl_mg_pll_write (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 int /*<<< orphan*/  icl_pll_id_to_enable_reg (int const) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void icl_pll_enable(struct drm_i915_private *dev_priv,
			   struct intel_shared_dpll *pll)
{
	const enum intel_dpll_id id = pll->info->id;
	i915_reg_t enable_reg = icl_pll_id_to_enable_reg(id);
	uint32_t val;

	val = I915_READ(enable_reg);
	val |= PLL_POWER_ENABLE;
	I915_WRITE(enable_reg, val);

	/*
	 * The spec says we need to "wait" but it also says it should be
	 * immediate.
	 */
	if (intel_wait_for_register(dev_priv, enable_reg, PLL_POWER_STATE,
				    PLL_POWER_STATE, 1))
		DRM_ERROR("PLL %d Power not enabled\n", id);

	switch (id) {
	case DPLL_ID_ICL_DPLL0:
	case DPLL_ID_ICL_DPLL1:
	case DPLL_ID_ICL_TBTPLL:
		icl_dpll_write(dev_priv, pll);
		break;
	case DPLL_ID_ICL_MGPLL1:
	case DPLL_ID_ICL_MGPLL2:
	case DPLL_ID_ICL_MGPLL3:
	case DPLL_ID_ICL_MGPLL4:
		icl_mg_pll_write(dev_priv, pll);
		break;
	default:
		MISSING_CASE(id);
	}

	/*
	 * DVFS pre sequence would be here, but in our driver the cdclk code
	 * paths should already be setting the appropriate voltage, hence we do
	 * nothign here.
	 */

	val = I915_READ(enable_reg);
	val |= PLL_ENABLE;
	I915_WRITE(enable_reg, val);

	if (intel_wait_for_register(dev_priv, enable_reg, PLL_LOCK, PLL_LOCK,
				    1)) /* 600us actually. */
		DRM_ERROR("PLL %d not locked\n", id);

	/* DVFS post sequence would be here. See the comment above. */
}