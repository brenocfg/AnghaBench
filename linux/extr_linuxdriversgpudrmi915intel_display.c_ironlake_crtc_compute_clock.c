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
struct intel_crtc_state {int /*<<< orphan*/  dpll; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  clock_set; int /*<<< orphan*/  has_pch_encoder; int /*<<< orphan*/  dpll_hw_state; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct TYPE_4__ {int lvds_ssc_freq; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 int /*<<< orphan*/  g4x_find_best_dpll (struct intel_limit const*,struct intel_crtc_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_shared_dpll (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_is_dual_link_lvds (struct drm_device*) ; 
 struct intel_limit intel_limits_ironlake_dac ; 
 struct intel_limit intel_limits_ironlake_dual_lvds ; 
 struct intel_limit intel_limits_ironlake_dual_lvds_100m ; 
 struct intel_limit intel_limits_ironlake_single_lvds ; 
 struct intel_limit intel_limits_ironlake_single_lvds_100m ; 
 scalar_t__ intel_panel_use_ssc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ironlake_compute_dpll (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int ironlake_crtc_compute_clock(struct intel_crtc *crtc,
				       struct intel_crtc_state *crtc_state)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	const struct intel_limit *limit;
	int refclk = 120000;

	memset(&crtc_state->dpll_hw_state, 0,
	       sizeof(crtc_state->dpll_hw_state));

	/* CPU eDP is the only output that doesn't need a PCH PLL of its own. */
	if (!crtc_state->has_pch_encoder)
		return 0;

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) {
		if (intel_panel_use_ssc(dev_priv)) {
			DRM_DEBUG_KMS("using SSC reference clock of %d kHz\n",
				      dev_priv->vbt.lvds_ssc_freq);
			refclk = dev_priv->vbt.lvds_ssc_freq;
		}

		if (intel_is_dual_link_lvds(dev)) {
			if (refclk == 100000)
				limit = &intel_limits_ironlake_dual_lvds_100m;
			else
				limit = &intel_limits_ironlake_dual_lvds;
		} else {
			if (refclk == 100000)
				limit = &intel_limits_ironlake_single_lvds_100m;
			else
				limit = &intel_limits_ironlake_single_lvds;
		}
	} else {
		limit = &intel_limits_ironlake_dac;
	}

	if (!crtc_state->clock_set &&
	    !g4x_find_best_dpll(limit, crtc_state, crtc_state->port_clock,
				refclk, NULL, &crtc_state->dpll)) {
		DRM_ERROR("Couldn't find PLL settings for mode!\n");
		return -EINVAL;
	}

	ironlake_compute_dpll(crtc, crtc_state, NULL);

	if (!intel_get_shared_dpll(crtc, crtc_state, NULL)) {
		DRM_DEBUG_DRIVER("failed to find PLL for pipe %c\n",
				 pipe_name(crtc->pipe));
		return -EINVAL;
	}

	return 0;
}