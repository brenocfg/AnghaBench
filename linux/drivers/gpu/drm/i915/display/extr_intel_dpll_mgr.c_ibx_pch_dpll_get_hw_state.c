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
struct intel_dpll_hw_state {int dpll; void* fp1; void* fp0; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int DPLL_VCO_ENABLE ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_DPLL (int const) ; 
 int /*<<< orphan*/  PCH_FP0 (int const) ; 
 int /*<<< orphan*/  PCH_FP1 (int const) ; 
 int /*<<< orphan*/  POWER_DOMAIN_DISPLAY_CORE ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ibx_pch_dpll_get_hw_state(struct drm_i915_private *dev_priv,
				      struct intel_shared_dpll *pll,
				      struct intel_dpll_hw_state *hw_state)
{
	const enum intel_dpll_id id = pll->info->id;
	intel_wakeref_t wakeref;
	u32 val;

	wakeref = intel_display_power_get_if_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	if (!wakeref)
		return false;

	val = I915_READ(PCH_DPLL(id));
	hw_state->dpll = val;
	hw_state->fp0 = I915_READ(PCH_FP0(id));
	hw_state->fp1 = I915_READ(PCH_FP1(id));

	intel_display_power_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	return val & DPLL_VCO_ENABLE;
}