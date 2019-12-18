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
struct intel_shared_dpll {TYPE_1__* info; } ;
struct intel_dpll_hw_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DPLL_ENABLE (scalar_t__) ; 
 scalar_t__ DPLL_ID_EHL_DPLL4 ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MG_PLL_ENABLE (int /*<<< orphan*/ ) ; 
 int icl_pll_get_hw_state (struct drm_i915_private*,struct intel_shared_dpll*,struct intel_dpll_hw_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool combo_pll_get_hw_state(struct drm_i915_private *dev_priv,
				   struct intel_shared_dpll *pll,
				   struct intel_dpll_hw_state *hw_state)
{
	i915_reg_t enable_reg = CNL_DPLL_ENABLE(pll->info->id);

	if (IS_ELKHARTLAKE(dev_priv) &&
	    pll->info->id == DPLL_ID_EHL_DPLL4) {
		enable_reg = MG_PLL_ENABLE(0);
	}

	return icl_pll_get_hw_state(dev_priv, pll, hw_state, enable_reg);
}