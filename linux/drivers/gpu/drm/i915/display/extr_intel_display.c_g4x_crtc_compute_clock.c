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
struct intel_limit {int dummy; } ;
struct intel_crtc_state {int /*<<< orphan*/  dpll; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  clock_set; int /*<<< orphan*/  dpll_hw_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct TYPE_4__ {int lvds_ssc_freq; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 int /*<<< orphan*/  g4x_find_best_dpll (struct intel_limit const*,struct intel_crtc_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i9xx_compute_dpll (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_is_dual_link_lvds (struct drm_i915_private*) ; 
 struct intel_limit intel_limits_g4x_dual_channel_lvds ; 
 struct intel_limit intel_limits_g4x_hdmi ; 
 struct intel_limit intel_limits_g4x_sdvo ; 
 struct intel_limit intel_limits_g4x_single_channel_lvds ; 
 struct intel_limit intel_limits_i9xx_sdvo ; 
 scalar_t__ intel_panel_use_ssc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g4x_crtc_compute_clock(struct intel_crtc *crtc,
				  struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const struct intel_limit *limit;
	int refclk = 96000;

	memset(&crtc_state->dpll_hw_state, 0,
	       sizeof(crtc_state->dpll_hw_state));

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) {
		if (intel_panel_use_ssc(dev_priv)) {
			refclk = dev_priv->vbt.lvds_ssc_freq;
			DRM_DEBUG_KMS("using SSC reference clock of %d kHz\n", refclk);
		}

		if (intel_is_dual_link_lvds(dev_priv))
			limit = &intel_limits_g4x_dual_channel_lvds;
		else
			limit = &intel_limits_g4x_single_channel_lvds;
	} else if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI) ||
		   intel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG)) {
		limit = &intel_limits_g4x_hdmi;
	} else if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO)) {
		limit = &intel_limits_g4x_sdvo;
	} else {
		/* The option is for other outputs */
		limit = &intel_limits_i9xx_sdvo;
	}

	if (!crtc_state->clock_set &&
	    !g4x_find_best_dpll(limit, crtc_state, crtc_state->port_clock,
				refclk, NULL, &crtc_state->dpll)) {
		DRM_ERROR("Couldn't find PLL settings for mode!\n");
		return -EINVAL;
	}

	i9xx_compute_dpll(crtc, crtc_state, NULL);

	return 0;
}