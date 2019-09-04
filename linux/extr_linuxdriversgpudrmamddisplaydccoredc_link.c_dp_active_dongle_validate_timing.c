#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dc_dongle_caps {scalar_t__ dongle_type; int extendedCapValid; int dp_hdmi_max_bpc; unsigned int dp_hdmi_max_pixel_clk; int /*<<< orphan*/  is_dp_hdmi_ycbcr420_pass_through; int /*<<< orphan*/  is_dp_hdmi_ycbcr422_pass_through; } ;
struct dpcd_caps {int dongle_type; struct dc_dongle_caps dongle_caps; } ;
struct dc_crtc_timing {unsigned int pix_clk_khz; int pixel_encoding; int display_color_depth; } ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 140 
#define  COLOR_DEPTH_121212 139 
#define  COLOR_DEPTH_141414 138 
#define  COLOR_DEPTH_161616 137 
#define  COLOR_DEPTH_666 136 
#define  COLOR_DEPTH_888 135 
#define  DISPLAY_DONGLE_DP_DVI_CONVERTER 134 
#define  DISPLAY_DONGLE_DP_DVI_DONGLE 133 
 scalar_t__ DISPLAY_DONGLE_DP_HDMI_CONVERTER ; 
#define  DISPLAY_DONGLE_DP_VGA_CONVERTER 132 
#define  PIXEL_ENCODING_RGB 131 
#define  PIXEL_ENCODING_YCBCR420 130 
#define  PIXEL_ENCODING_YCBCR422 129 
#define  PIXEL_ENCODING_YCBCR444 128 

__attribute__((used)) static bool dp_active_dongle_validate_timing(
		const struct dc_crtc_timing *timing,
		const struct dpcd_caps *dpcd_caps)
{
	unsigned int required_pix_clk = timing->pix_clk_khz;
	const struct dc_dongle_caps *dongle_caps = &dpcd_caps->dongle_caps;

	switch (dpcd_caps->dongle_type) {
	case DISPLAY_DONGLE_DP_VGA_CONVERTER:
	case DISPLAY_DONGLE_DP_DVI_CONVERTER:
	case DISPLAY_DONGLE_DP_DVI_DONGLE:
		if (timing->pixel_encoding == PIXEL_ENCODING_RGB)
			return true;
		else
			return false;
	default:
		break;
	}

	if (dongle_caps->dongle_type != DISPLAY_DONGLE_DP_HDMI_CONVERTER ||
		dongle_caps->extendedCapValid == false)
		return true;

	/* Check Pixel Encoding */
	switch (timing->pixel_encoding) {
	case PIXEL_ENCODING_RGB:
	case PIXEL_ENCODING_YCBCR444:
		break;
	case PIXEL_ENCODING_YCBCR422:
		if (!dongle_caps->is_dp_hdmi_ycbcr422_pass_through)
			return false;
		break;
	case PIXEL_ENCODING_YCBCR420:
		if (!dongle_caps->is_dp_hdmi_ycbcr420_pass_through)
			return false;
		break;
	default:
		/* Invalid Pixel Encoding*/
		return false;
	}


	/* Check Color Depth and Pixel Clock */
	if (timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		required_pix_clk /= 2;
	else if (timing->pixel_encoding == PIXEL_ENCODING_YCBCR422)
		required_pix_clk = required_pix_clk * 2 / 3;

	switch (timing->display_color_depth) {
	case COLOR_DEPTH_666:
	case COLOR_DEPTH_888:
		/*888 and 666 should always be supported*/
		break;
	case COLOR_DEPTH_101010:
		if (dongle_caps->dp_hdmi_max_bpc < 10)
			return false;
		required_pix_clk = required_pix_clk * 10 / 8;
		break;
	case COLOR_DEPTH_121212:
		if (dongle_caps->dp_hdmi_max_bpc < 12)
			return false;
		required_pix_clk = required_pix_clk * 12 / 8;
		break;

	case COLOR_DEPTH_141414:
	case COLOR_DEPTH_161616:
	default:
		/* These color depths are currently not supported */
		return false;
	}

	if (required_pix_clk > dongle_caps->dp_hdmi_max_pixel_clk)
		return false;

	return true;
}