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
struct intel_dpll_hw_state {int /*<<< orphan*/  mg_pll_tdc_coldst_bias; int /*<<< orphan*/  mg_pll_bias; int /*<<< orphan*/  mg_pll_ssc; int /*<<< orphan*/  mg_pll_frac_lock; int /*<<< orphan*/  mg_pll_lf; int /*<<< orphan*/  mg_pll_div1; int /*<<< orphan*/  mg_pll_div0; int /*<<< orphan*/  mg_clktop2_hsclkctl; int /*<<< orphan*/  mg_clktop2_coreclkctl1; int /*<<< orphan*/  mg_refclkin_ctl; int /*<<< orphan*/  cfgcr1; int /*<<< orphan*/  cfgcr0; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_dump_hw_state(struct drm_i915_private *dev_priv,
			      const struct intel_dpll_hw_state *hw_state)
{
	DRM_DEBUG_KMS("dpll_hw_state: cfgcr0: 0x%x, cfgcr1: 0x%x, "
		      "mg_refclkin_ctl: 0x%x, hg_clktop2_coreclkctl1: 0x%x, "
		      "mg_clktop2_hsclkctl: 0x%x, mg_pll_div0: 0x%x, "
		      "mg_pll_div2: 0x%x, mg_pll_lf: 0x%x, "
		      "mg_pll_frac_lock: 0x%x, mg_pll_ssc: 0x%x, "
		      "mg_pll_bias: 0x%x, mg_pll_tdc_coldst_bias: 0x%x\n",
		      hw_state->cfgcr0, hw_state->cfgcr1,
		      hw_state->mg_refclkin_ctl,
		      hw_state->mg_clktop2_coreclkctl1,
		      hw_state->mg_clktop2_hsclkctl,
		      hw_state->mg_pll_div0,
		      hw_state->mg_pll_div1,
		      hw_state->mg_pll_lf,
		      hw_state->mg_pll_frac_lock,
		      hw_state->mg_pll_ssc,
		      hw_state->mg_pll_bias,
		      hw_state->mg_pll_tdc_coldst_bias);
}