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
typedef  scalar_t__ uint32_t ;
struct dpcd_caps {int dummy; } ;
struct dc_stream_state {int signal; TYPE_1__* link; } ;
struct dc_link {scalar_t__* remote_sinks; struct dpcd_caps dpcd_caps; } ;
struct dc_crtc_timing {int dummy; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_2__ {int dongle_max_pix_clk; } ;

/* Variables and functions */
 int DC_EXCEED_DONGLE_CAP ; 
 int DC_NO_DP_LINK_BANDWIDTH ; 
 int DC_OK ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 129 
#define  SIGNAL_TYPE_EDP 128 
 int /*<<< orphan*/  dp_active_dongle_validate_timing (struct dc_crtc_timing const*,struct dpcd_caps*) ; 
 int /*<<< orphan*/  dp_validate_mode_timing (struct dc_link*,struct dc_crtc_timing const*) ; 
 scalar_t__ get_timing_pixel_clock_100hz (struct dc_crtc_timing const*) ; 

enum dc_status dc_link_validate_mode_timing(
		const struct dc_stream_state *stream,
		struct dc_link *link,
		const struct dc_crtc_timing *timing)
{
	uint32_t max_pix_clk = stream->link->dongle_max_pix_clk * 10;
	struct dpcd_caps *dpcd_caps = &link->dpcd_caps;

	/* A hack to avoid failing any modes for EDID override feature on
	 * topology change such as lower quality cable for DP or different dongle
	 */
	if (link->remote_sinks[0])
		return DC_OK;

	/* Passive Dongle */
	if (max_pix_clk != 0 && get_timing_pixel_clock_100hz(timing) > max_pix_clk)
		return DC_EXCEED_DONGLE_CAP;

	/* Active Dongle*/
	if (!dp_active_dongle_validate_timing(timing, dpcd_caps))
		return DC_EXCEED_DONGLE_CAP;

	switch (stream->signal) {
	case SIGNAL_TYPE_EDP:
	case SIGNAL_TYPE_DISPLAY_PORT:
		if (!dp_validate_mode_timing(
				link,
				timing))
			return DC_NO_DP_LINK_BANDWIDTH;
		break;

	default:
		break;
	}

	return DC_OK;
}