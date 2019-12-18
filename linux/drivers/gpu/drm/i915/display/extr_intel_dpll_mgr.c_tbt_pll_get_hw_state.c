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
struct intel_shared_dpll {int dummy; } ;
struct intel_dpll_hw_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TBT_PLL_ENABLE ; 
 int icl_pll_get_hw_state (struct drm_i915_private*,struct intel_shared_dpll*,struct intel_dpll_hw_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tbt_pll_get_hw_state(struct drm_i915_private *dev_priv,
				 struct intel_shared_dpll *pll,
				 struct intel_dpll_hw_state *hw_state)
{
	return icl_pll_get_hw_state(dev_priv, pll, hw_state, TBT_PLL_ENABLE);
}