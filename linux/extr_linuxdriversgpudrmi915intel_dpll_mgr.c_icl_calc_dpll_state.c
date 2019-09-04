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
typedef  void* uint32_t ;
struct skl_wrpll_params {int dco_integer; int /*<<< orphan*/  pdiv; int /*<<< orphan*/  kdiv; int /*<<< orphan*/  qdiv_mode; int /*<<< orphan*/  qdiv_ratio; int /*<<< orphan*/  dco_fraction; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_dpll_hw_state {void* cfgcr1; void* cfgcr0; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DPLL_CFGCR0_DCO_FRACTION (int /*<<< orphan*/ ) ; 
 int DPLL_CFGCR1_CENTRAL_FREQ_8400 ; 
 int DPLL_CFGCR1_KDIV (int /*<<< orphan*/ ) ; 
 int DPLL_CFGCR1_PDIV (int /*<<< orphan*/ ) ; 
 int DPLL_CFGCR1_QDIV_MODE (int /*<<< orphan*/ ) ; 
 int DPLL_CFGCR1_QDIV_RATIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int cnl_ddi_calculate_wrpll (int,struct drm_i915_private*,struct skl_wrpll_params*) ; 
 int icl_calc_dp_combo_pll (struct drm_i915_private*,int,struct skl_wrpll_params*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool icl_calc_dpll_state(struct intel_crtc_state *crtc_state,
				struct intel_encoder *encoder, int clock,
				struct intel_dpll_hw_state *pll_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	uint32_t cfgcr0, cfgcr1;
	struct skl_wrpll_params pll_params = { 0 };
	bool ret;

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		ret = cnl_ddi_calculate_wrpll(clock, dev_priv, &pll_params);
	else
		ret = icl_calc_dp_combo_pll(dev_priv, clock, &pll_params);

	if (!ret)
		return false;

	cfgcr0 = DPLL_CFGCR0_DCO_FRACTION(pll_params.dco_fraction) |
		 pll_params.dco_integer;

	cfgcr1 = DPLL_CFGCR1_QDIV_RATIO(pll_params.qdiv_ratio) |
		 DPLL_CFGCR1_QDIV_MODE(pll_params.qdiv_mode) |
		 DPLL_CFGCR1_KDIV(pll_params.kdiv) |
		 DPLL_CFGCR1_PDIV(pll_params.pdiv) |
		 DPLL_CFGCR1_CENTRAL_FREQ_8400;

	pll_state->cfgcr0 = cfgcr0;
	pll_state->cfgcr1 = cfgcr1;
	return true;
}