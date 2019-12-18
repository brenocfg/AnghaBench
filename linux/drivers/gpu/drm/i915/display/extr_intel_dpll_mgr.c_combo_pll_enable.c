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
struct intel_shared_dpll {int /*<<< orphan*/  wakeref; TYPE_1__* info; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DPLL_ENABLE (scalar_t__) ; 
 scalar_t__ DPLL_ID_EHL_DPLL4 ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MG_PLL_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_DOMAIN_DPLL_DC_OFF ; 
 int /*<<< orphan*/  icl_dpll_write (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 int /*<<< orphan*/  icl_pll_enable (struct drm_i915_private*,struct intel_shared_dpll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_pll_power_enable (struct drm_i915_private*,struct intel_shared_dpll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void combo_pll_enable(struct drm_i915_private *dev_priv,
			     struct intel_shared_dpll *pll)
{
	i915_reg_t enable_reg = CNL_DPLL_ENABLE(pll->info->id);

	if (IS_ELKHARTLAKE(dev_priv) &&
	    pll->info->id == DPLL_ID_EHL_DPLL4) {
		enable_reg = MG_PLL_ENABLE(0);

		/*
		 * We need to disable DC states when this DPLL is enabled.
		 * This can be done by taking a reference on DPLL4 power
		 * domain.
		 */
		pll->wakeref = intel_display_power_get(dev_priv,
						       POWER_DOMAIN_DPLL_DC_OFF);
	}

	icl_pll_power_enable(dev_priv, pll, enable_reg);

	icl_dpll_write(dev_priv, pll);

	/*
	 * DVFS pre sequence would be here, but in our driver the cdclk code
	 * paths should already be setting the appropriate voltage, hence we do
	 * nothing here.
	 */

	icl_pll_enable(dev_priv, pll, enable_reg);

	/* DVFS post sequence would be here. See the comment above. */
}