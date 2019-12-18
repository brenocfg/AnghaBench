#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int dpll; int fp0; int fp1; } ;
struct dpll {int m; int n; int p1; int p2; } ;
struct intel_crtc_state {int pixel_multiplier; TYPE_3__ dpll_hw_state; struct dpll dpll; scalar_t__ sdvo_tv_clock; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct TYPE_6__ {int lvds_ssc_freq; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct TYPE_8__ {int num_pipes; } ;

/* Variables and functions */
 int DPLLB_LVDS_P2_CLOCK_DIV_14 ; 
 int DPLLB_LVDS_P2_CLOCK_DIV_7 ; 
 int DPLLB_MODE_DAC_SERIAL ; 
 int DPLLB_MODE_LVDS ; 
 int DPLL_DAC_SERIAL_P2_CLOCK_DIV_10 ; 
 int DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT ; 
 int DPLL_FPA1_P1_POST_DIV_SHIFT ; 
 int DPLL_SDVO_HIGH_SPEED ; 
 int DPLL_VCO_ENABLE ; 
 int FP_CB_TUNE ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 TYPE_4__* INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 int PLLB_REF_INPUT_SPREADSPECTRUMIN ; 
 int PLL_REF_INPUT_DREFCLK ; 
 int PLL_REF_SDVO_HDMI_MULTIPLIER_SHIFT ; 
 int i9xx_dpll_compute_fp (struct dpll*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_is_dual_link_lvds (struct drm_i915_private*) ; 
 scalar_t__ intel_panel_use_ssc (struct drm_i915_private*) ; 
 scalar_t__ ironlake_needs_fb_cb_tune (struct dpll*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ironlake_compute_dpll(struct intel_crtc *crtc,
				  struct intel_crtc_state *crtc_state,
				  struct dpll *reduced_clock)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	u32 dpll, fp, fp2;
	int factor;

	/* Enable autotuning of the PLL clock (if permissible) */
	factor = 21;
	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) {
		if ((intel_panel_use_ssc(dev_priv) &&
		     dev_priv->vbt.lvds_ssc_freq == 100000) ||
		    (HAS_PCH_IBX(dev_priv) &&
		     intel_is_dual_link_lvds(dev_priv)))
			factor = 25;
	} else if (crtc_state->sdvo_tv_clock) {
		factor = 20;
	}

	fp = i9xx_dpll_compute_fp(&crtc_state->dpll);

	if (ironlake_needs_fb_cb_tune(&crtc_state->dpll, factor))
		fp |= FP_CB_TUNE;

	if (reduced_clock) {
		fp2 = i9xx_dpll_compute_fp(reduced_clock);

		if (reduced_clock->m < factor * reduced_clock->n)
			fp2 |= FP_CB_TUNE;
	} else {
		fp2 = fp;
	}

	dpll = 0;

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS))
		dpll |= DPLLB_MODE_LVDS;
	else
		dpll |= DPLLB_MODE_DAC_SERIAL;

	dpll |= (crtc_state->pixel_multiplier - 1)
		<< PLL_REF_SDVO_HDMI_MULTIPLIER_SHIFT;

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO) ||
	    intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	if (intel_crtc_has_dp_encoder(crtc_state))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	/*
	 * The high speed IO clock is only really required for
	 * SDVO/HDMI/DP, but we also enable it for CRT to make it
	 * possible to share the DPLL between CRT and HDMI. Enabling
	 * the clock needlessly does no real harm, except use up a
	 * bit of power potentially.
	 *
	 * We'll limit this to IVB with 3 pipes, since it has only two
	 * DPLLs and so DPLL sharing is the only way to get three pipes
	 * driving PCH ports at the same time. On SNB we could do this,
	 * and potentially avoid enabling the second DPLL, but it's not
	 * clear if it''s a win or loss power wise. No point in doing
	 * this on ILK at all since it has a fixed DPLL<->pipe mapping.
	 */
	if (INTEL_INFO(dev_priv)->num_pipes == 3 &&
	    intel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	/* compute bitmask from p1 value */
	dpll |= (1 << (crtc_state->dpll.p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT;
	/* also FPA1 */
	dpll |= (1 << (crtc_state->dpll.p1 - 1)) << DPLL_FPA1_P1_POST_DIV_SHIFT;

	switch (crtc_state->dpll.p2) {
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

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS) &&
	    intel_panel_use_ssc(dev_priv))
		dpll |= PLLB_REF_INPUT_SPREADSPECTRUMIN;
	else
		dpll |= PLL_REF_INPUT_DREFCLK;

	dpll |= DPLL_VCO_ENABLE;

	crtc_state->dpll_hw_state.dpll = dpll;
	crtc_state->dpll_hw_state.fp0 = fp;
	crtc_state->dpll_hw_state.fp1 = fp2;
}