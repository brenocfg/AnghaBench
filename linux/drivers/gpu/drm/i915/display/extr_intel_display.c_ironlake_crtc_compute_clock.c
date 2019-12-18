#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_limit {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct intel_crtc_state {int /*<<< orphan*/  dpll; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  clock_set; int /*<<< orphan*/  has_pch_encoder; int /*<<< orphan*/  dpll_hw_state; TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_6__ {int lvds_ssc_freq; } ;
struct drm_i915_private {TYPE_3__ vbt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 int /*<<< orphan*/  g4x_find_best_dpll (struct intel_limit const*,struct intel_crtc_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_is_dual_link_lvds (struct drm_i915_private*) ; 
 struct intel_limit intel_limits_ironlake_dac ; 
 struct intel_limit intel_limits_ironlake_dual_lvds ; 
 struct intel_limit intel_limits_ironlake_dual_lvds_100m ; 
 struct intel_limit intel_limits_ironlake_single_lvds ; 
 struct intel_limit intel_limits_ironlake_single_lvds_100m ; 
 scalar_t__ intel_panel_use_ssc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_reserve_shared_dplls (struct intel_atomic_state*,struct intel_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ironlake_compute_dpll (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pipe_name (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ironlake_crtc_compute_clock(struct intel_crtc *crtc,
				       struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_atomic_state *state =
		to_intel_atomic_state(crtc_state->base.state);
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

		if (intel_is_dual_link_lvds(dev_priv)) {
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

	if (!intel_reserve_shared_dplls(state, crtc, NULL)) {
		DRM_DEBUG_KMS("failed to find PLL for pipe %c\n",
			      pipe_name(crtc->pipe));
		return -EINVAL;
	}

	return 0;
}