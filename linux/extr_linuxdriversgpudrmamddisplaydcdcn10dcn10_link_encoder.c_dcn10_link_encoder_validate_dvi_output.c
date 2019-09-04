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
typedef  int uint32_t ;
struct TYPE_3__ {int max_hdmi_pixel_clock; } ;
struct TYPE_4__ {TYPE_1__ features; } ;
struct dcn10_link_encoder {TYPE_2__ base; } ;
struct dc_crtc_timing {scalar_t__ pixel_encoding; int pix_clk_khz; int display_color_depth; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_161616 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 scalar_t__ PIXEL_ENCODING_RGB ; 
 int SIGNAL_TYPE_DVI_DUAL_LINK ; 
 int SIGNAL_TYPE_DVI_SINGLE_LINK ; 
 int SIGNAL_TYPE_HDMI_TYPE_A ; 
 int TMDS_MAX_PIXEL_CLOCK ; 
 int TMDS_MIN_PIXEL_CLOCK ; 

bool dcn10_link_encoder_validate_dvi_output(
	const struct dcn10_link_encoder *enc10,
	enum signal_type connector_signal,
	enum signal_type signal,
	const struct dc_crtc_timing *crtc_timing)
{
	uint32_t max_pixel_clock = TMDS_MAX_PIXEL_CLOCK;

	if (signal == SIGNAL_TYPE_DVI_DUAL_LINK)
		max_pixel_clock *= 2;

	/* This handles the case of HDMI downgrade to DVI we don't want to
	 * we don't want to cap the pixel clock if the DDI is not DVI.
	 */
	if (connector_signal != SIGNAL_TYPE_DVI_DUAL_LINK &&
			connector_signal != SIGNAL_TYPE_DVI_SINGLE_LINK)
		max_pixel_clock = enc10->base.features.max_hdmi_pixel_clock;

	/* DVI only support RGB pixel encoding */
	if (crtc_timing->pixel_encoding != PIXEL_ENCODING_RGB)
		return false;

	/*connect DVI via adpater's HDMI connector*/
	if ((connector_signal == SIGNAL_TYPE_DVI_SINGLE_LINK ||
		connector_signal == SIGNAL_TYPE_HDMI_TYPE_A) &&
		signal != SIGNAL_TYPE_HDMI_TYPE_A &&
		crtc_timing->pix_clk_khz > TMDS_MAX_PIXEL_CLOCK)
		return false;
	if (crtc_timing->pix_clk_khz < TMDS_MIN_PIXEL_CLOCK)
		return false;

	if (crtc_timing->pix_clk_khz > max_pixel_clock)
		return false;

	/* DVI supports 6/8bpp single-link and 10/16bpp dual-link */
	switch (crtc_timing->display_color_depth) {
	case COLOR_DEPTH_666:
	case COLOR_DEPTH_888:
	break;
	case COLOR_DEPTH_101010:
	case COLOR_DEPTH_161616:
		if (signal != SIGNAL_TYPE_DVI_DUAL_LINK)
			return false;
	break;
	default:
		return false;
	}

	return true;
}