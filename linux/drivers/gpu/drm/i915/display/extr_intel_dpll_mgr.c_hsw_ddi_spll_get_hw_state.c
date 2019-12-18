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
struct intel_shared_dpll {int dummy; } ;
struct intel_dpll_hw_state {int spll; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_DOMAIN_DISPLAY_CORE ; 
 int /*<<< orphan*/  SPLL_CTL ; 
 int SPLL_PLL_ENABLE ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hsw_ddi_spll_get_hw_state(struct drm_i915_private *dev_priv,
				      struct intel_shared_dpll *pll,
				      struct intel_dpll_hw_state *hw_state)
{
	intel_wakeref_t wakeref;
	u32 val;

	wakeref = intel_display_power_get_if_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	if (!wakeref)
		return false;

	val = I915_READ(SPLL_CTL);
	hw_state->spll = val;

	intel_display_power_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	return val & SPLL_PLL_ENABLE;
}