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
struct link_config_limits {int max_bpp; int min_bpp; int min_clock; int max_clock; int min_lane_count; int max_lane_count; } ;
struct intel_dp {int* common_rates; } ;
struct drm_display_mode {int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int lane_count; int pipe_bpp; int port_clock; TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int intel_dp_link_required (int /*<<< orphan*/ ,int) ; 
 int intel_dp_max_data_rate (int,int) ; 
 int intel_dp_output_bpp (struct intel_crtc_state*,int) ; 

__attribute__((used)) static int
intel_dp_compute_link_config_wide(struct intel_dp *intel_dp,
				  struct intel_crtc_state *pipe_config,
				  const struct link_config_limits *limits)
{
	struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	int bpp, clock, lane_count;
	int mode_rate, link_clock, link_avail;

	for (bpp = limits->max_bpp; bpp >= limits->min_bpp; bpp -= 2 * 3) {
		int output_bpp = intel_dp_output_bpp(pipe_config, bpp);

		mode_rate = intel_dp_link_required(adjusted_mode->crtc_clock,
						   output_bpp);

		for (clock = limits->min_clock; clock <= limits->max_clock; clock++) {
			for (lane_count = limits->min_lane_count;
			     lane_count <= limits->max_lane_count;
			     lane_count <<= 1) {
				link_clock = intel_dp->common_rates[clock];
				link_avail = intel_dp_max_data_rate(link_clock,
								    lane_count);

				if (mode_rate <= link_avail) {
					pipe_config->lane_count = lane_count;
					pipe_config->pipe_bpp = bpp;
					pipe_config->port_clock = link_clock;

					return 0;
				}
			}
		}
	}

	return -EINVAL;
}