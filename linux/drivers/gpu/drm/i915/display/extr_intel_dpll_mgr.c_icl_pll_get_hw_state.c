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
typedef  int u32 ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct intel_dpll_hw_state {void* cfgcr1; void* cfgcr0; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int const DPLL_ID_EHL_DPLL4 ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR0 (int const) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR1 (int const) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 int PLL_ENABLE ; 
 int /*<<< orphan*/  POWER_DOMAIN_DISPLAY_CORE ; 
 int /*<<< orphan*/  TGL_DPLL_CFGCR0 (int const) ; 
 int /*<<< orphan*/  TGL_DPLL_CFGCR1 (int const) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool icl_pll_get_hw_state(struct drm_i915_private *dev_priv,
				 struct intel_shared_dpll *pll,
				 struct intel_dpll_hw_state *hw_state,
				 i915_reg_t enable_reg)
{
	const enum intel_dpll_id id = pll->info->id;
	intel_wakeref_t wakeref;
	bool ret = false;
	u32 val;

	wakeref = intel_display_power_get_if_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	if (!wakeref)
		return false;

	val = I915_READ(enable_reg);
	if (!(val & PLL_ENABLE))
		goto out;

	if (INTEL_GEN(dev_priv) >= 12) {
		hw_state->cfgcr0 = I915_READ(TGL_DPLL_CFGCR0(id));
		hw_state->cfgcr1 = I915_READ(TGL_DPLL_CFGCR1(id));
	} else {
		if (IS_ELKHARTLAKE(dev_priv) && id == DPLL_ID_EHL_DPLL4) {
			hw_state->cfgcr0 = I915_READ(ICL_DPLL_CFGCR0(4));
			hw_state->cfgcr1 = I915_READ(ICL_DPLL_CFGCR1(4));
		} else {
			hw_state->cfgcr0 = I915_READ(ICL_DPLL_CFGCR0(id));
			hw_state->cfgcr1 = I915_READ(ICL_DPLL_CFGCR1(id));
		}
	}

	ret = true;
out:
	intel_display_power_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
	return ret;
}