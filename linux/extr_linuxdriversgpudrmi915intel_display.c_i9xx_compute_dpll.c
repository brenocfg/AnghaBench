#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int dpll; int dpll_md; } ;
struct dpll {int p1; int p2; } ;
struct intel_crtc_state {int pixel_multiplier; TYPE_2__ dpll_hw_state; scalar_t__ sdvo_tv_clock; struct dpll dpll; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DPLLB_LVDS_P2_CLOCK_DIV_14 ; 
 int DPLLB_LVDS_P2_CLOCK_DIV_7 ; 
 int DPLLB_MODE_DAC_SERIAL ; 
 int DPLLB_MODE_LVDS ; 
 int DPLL_DAC_SERIAL_P2_CLOCK_DIV_10 ; 
 int DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW ; 
 int DPLL_FPA1_P1_POST_DIV_SHIFT ; 
 int DPLL_MD_UDI_MULTIPLIER_SHIFT ; 
 int DPLL_SDVO_HIGH_SPEED ; 
 int DPLL_VCO_ENABLE ; 
 int DPLL_VGA_MODE_DIS ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 scalar_t__ IS_G33 (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_I945G (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 int PLLB_REF_INPUT_SPREADSPECTRUMIN ; 
 int PLL_LOAD_PULSE_PHASE_SHIFT ; 
 int PLL_REF_INPUT_DREFCLK ; 
 int PLL_REF_INPUT_TVCLKINBC ; 
 int SDVO_MULTIPLIER_SHIFT_HIRES ; 
 int /*<<< orphan*/  i9xx_update_pll_dividers (struct intel_crtc*,struct intel_crtc_state*,struct dpll*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_panel_use_ssc (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_compute_dpll(struct intel_crtc *crtc,
			      struct intel_crtc_state *crtc_state,
			      struct dpll *reduced_clock)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	u32 dpll;
	struct dpll *clock = &crtc_state->dpll;

	i9xx_update_pll_dividers(crtc, crtc_state, reduced_clock);

	dpll = DPLL_VGA_MODE_DIS;

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS))
		dpll |= DPLLB_MODE_LVDS;
	else
		dpll |= DPLLB_MODE_DAC_SERIAL;

	if (IS_I945G(dev_priv) || IS_I945GM(dev_priv) ||
	    IS_G33(dev_priv) || IS_PINEVIEW(dev_priv)) {
		dpll |= (crtc_state->pixel_multiplier - 1)
			<< SDVO_MULTIPLIER_SHIFT_HIRES;
	}

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO) ||
	    intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	if (intel_crtc_has_dp_encoder(crtc_state))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	/* compute bitmask from p1 value */
	if (IS_PINEVIEW(dev_priv))
		dpll |= (1 << (clock->p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW;
	else {
		dpll |= (1 << (clock->p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT;
		if (IS_G4X(dev_priv) && reduced_clock)
			dpll |= (1 << (reduced_clock->p1 - 1)) << DPLL_FPA1_P1_POST_DIV_SHIFT;
	}
	switch (clock->p2) {
	case 5:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_5;
		break;
	case 7:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_7;
		break;
	case 10:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_10;
		break;
	case 14:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_14;
		break;
	}
	if (INTEL_GEN(dev_priv) >= 4)
		dpll |= (6 << PLL_LOAD_PULSE_PHASE_SHIFT);

	if (crtc_state->sdvo_tv_clock)
		dpll |= PLL_REF_INPUT_TVCLKINBC;
	else if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS) &&
		 intel_panel_use_ssc(dev_priv))
		dpll |= PLLB_REF_INPUT_SPREADSPECTRUMIN;
	else
		dpll |= PLL_REF_INPUT_DREFCLK;

	dpll |= DPLL_VCO_ENABLE;
	crtc_state->dpll_hw_state.dpll = dpll;

	if (INTEL_GEN(dev_priv) >= 4) {
		u32 dpll_md = (crtc_state->pixel_multiplier - 1)
			<< DPLL_MD_UDI_MULTIPLIER_SHIFT;
		crtc_state->dpll_hw_state.dpll_md = dpll_md;
	}
}