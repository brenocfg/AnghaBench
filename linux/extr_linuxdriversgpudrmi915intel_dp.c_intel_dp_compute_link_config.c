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
struct link_config_limits {int min_clock; int max_clock; int min_lane_count; int max_lane_count; int min_bpp; int /*<<< orphan*/  max_bpp; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int /*<<< orphan*/ * common_rates; int /*<<< orphan*/  max_link_rate; } ;
struct drm_display_mode {int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int /*<<< orphan*/  lane_count; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  pipe_bpp; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_adjust_compliance_config (struct intel_dp*,struct intel_crtc_state*,struct link_config_limits*) ; 
 int intel_dp_common_len_rate_limit (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_compute_bpp (struct intel_dp*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_dp_compute_link_config_wide (struct intel_dp*,struct intel_crtc_state*,struct link_config_limits*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_link_required (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_max_data_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intel_dp_max_lane_count (struct intel_dp*) ; 

__attribute__((used)) static bool
intel_dp_compute_link_config(struct intel_encoder *encoder,
			     struct intel_crtc_state *pipe_config)
{
	struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct link_config_limits limits;
	int common_len;

	common_len = intel_dp_common_len_rate_limit(intel_dp,
						    intel_dp->max_link_rate);

	/* No common link rates between source and sink */
	WARN_ON(common_len <= 0);

	limits.min_clock = 0;
	limits.max_clock = common_len - 1;

	limits.min_lane_count = 1;
	limits.max_lane_count = intel_dp_max_lane_count(intel_dp);

	limits.min_bpp = 6 * 3;
	limits.max_bpp = intel_dp_compute_bpp(intel_dp, pipe_config);

	if (intel_dp_is_edp(intel_dp)) {
		/*
		 * Use the maximum clock and number of lanes the eDP panel
		 * advertizes being capable of. The panels are generally
		 * designed to support only a single clock and lane
		 * configuration, and typically these values correspond to the
		 * native resolution of the panel.
		 */
		limits.min_lane_count = limits.max_lane_count;
		limits.min_clock = limits.max_clock;
	}

	intel_dp_adjust_compliance_config(intel_dp, pipe_config, &limits);

	DRM_DEBUG_KMS("DP link computation with max lane count %i "
		      "max rate %d max bpp %d pixel clock %iKHz\n",
		      limits.max_lane_count,
		      intel_dp->common_rates[limits.max_clock],
		      limits.max_bpp, adjusted_mode->crtc_clock);

	/*
	 * Optimize for slow and wide. This is the place to add alternative
	 * optimization policy.
	 */
	if (!intel_dp_compute_link_config_wide(intel_dp, pipe_config, &limits))
		return false;

	DRM_DEBUG_KMS("DP lane count %d clock %d bpp %d\n",
		      pipe_config->lane_count, pipe_config->port_clock,
		      pipe_config->pipe_bpp);

	DRM_DEBUG_KMS("DP link rate required %i available %i\n",
		      intel_dp_link_required(adjusted_mode->crtc_clock,
					     pipe_config->pipe_bpp),
		      intel_dp_max_data_rate(pipe_config->port_clock,
					     pipe_config->lane_count));

	return true;
}