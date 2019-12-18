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
struct link_config_limits {int min_bpp; int max_bpp; int min_clock; int max_clock; int /*<<< orphan*/  max_lane_count; int /*<<< orphan*/  min_lane_count; } ;
struct TYPE_3__ {int bpc; } ;
struct TYPE_4__ {scalar_t__ test_type; int /*<<< orphan*/  test_lane_count; int /*<<< orphan*/  test_link_rate; TYPE_1__ test_data; } ;
struct intel_dp {TYPE_2__ compliance; int /*<<< orphan*/  num_common_rates; int /*<<< orphan*/  common_rates; } ;
struct intel_crtc_state {int dither_force_disable; } ;

/* Variables and functions */
 scalar_t__ DP_TEST_LINK_TRAINING ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 scalar_t__ intel_dp_link_params_valid (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intel_dp_rate_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
intel_dp_adjust_compliance_config(struct intel_dp *intel_dp,
				  struct intel_crtc_state *pipe_config,
				  struct link_config_limits *limits)
{
	/* For DP Compliance we override the computed bpp for the pipe */
	if (intel_dp->compliance.test_data.bpc != 0) {
		int bpp = 3 * intel_dp->compliance.test_data.bpc;

		limits->min_bpp = limits->max_bpp = bpp;
		pipe_config->dither_force_disable = bpp == 6 * 3;

		DRM_DEBUG_KMS("Setting pipe_bpp to %d\n", bpp);
	}

	/* Use values requested by Compliance Test Request */
	if (intel_dp->compliance.test_type == DP_TEST_LINK_TRAINING) {
		int index;

		/* Validate the compliance test data since max values
		 * might have changed due to link train fallback.
		 */
		if (intel_dp_link_params_valid(intel_dp, intel_dp->compliance.test_link_rate,
					       intel_dp->compliance.test_lane_count)) {
			index = intel_dp_rate_index(intel_dp->common_rates,
						    intel_dp->num_common_rates,
						    intel_dp->compliance.test_link_rate);
			if (index >= 0)
				limits->min_clock = limits->max_clock = index;
			limits->min_lane_count = limits->max_lane_count =
				intel_dp->compliance.test_lane_count;
		}
	}
}