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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct stream_encoder {int dummy; } ;
struct dcn10_stream_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  VSYNC_POSITIVE_POLARITY; int /*<<< orphan*/  HSYNC_POSITIVE_POLARITY; int /*<<< orphan*/  Y_ONLY; } ;
struct dc_crtc_timing {int pixel_encoding; int display_color_depth; int h_total; int v_total; int h_border_left; int h_addressable; int h_border_right; int h_front_porch; int h_sync_width; int v_border_top; int v_addressable; int v_border_bottom; int v_front_porch; TYPE_1__ flags; int /*<<< orphan*/  v_sync_width; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 155 
#define  COLOR_DEPTH_121212 154 
#define  COLOR_DEPTH_161616 153 
#define  COLOR_DEPTH_666 152 
#define  COLOR_DEPTH_888 151 
#define  COLOR_SPACE_2020_RGB_FULLRANGE 150 
#define  COLOR_SPACE_2020_RGB_LIMITEDRANGE 149 
#define  COLOR_SPACE_2020_YCBCR 148 
#define  COLOR_SPACE_ADOBERGB 147 
#define  COLOR_SPACE_APPCTRL 146 
#define  COLOR_SPACE_CUSTOMPOINTS 145 
#define  COLOR_SPACE_DCIP3 144 
#define  COLOR_SPACE_DISPLAYNATIVE 143 
#define  COLOR_SPACE_DOLBYVISION 142 
#define  COLOR_SPACE_MSREF_SCRGB 141 
#define  COLOR_SPACE_SRGB 140 
#define  COLOR_SPACE_SRGB_LIMITED 139 
#define  COLOR_SPACE_UNKNOWN 138 
#define  COLOR_SPACE_XR_RGB 137 
#define  COLOR_SPACE_XV_YCC_601 136 
#define  COLOR_SPACE_XV_YCC_709 135 
#define  COLOR_SPACE_YCBCR601 134 
#define  COLOR_SPACE_YCBCR601_LIMITED 133 
#define  COLOR_SPACE_YCBCR709 132 
#define  COLOR_SPACE_YCBCR709_LIMITED 131 
 struct dcn10_stream_encoder* DCN10STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_COMPONENT_DEPTH ; 
 int DP_COMPONENT_PIXEL_DEPTH_10BPC ; 
 int DP_COMPONENT_PIXEL_DEPTH_12BPC ; 
 int DP_COMPONENT_PIXEL_DEPTH_16BPC ; 
 int DP_COMPONENT_PIXEL_DEPTH_6BPC ; 
 int DP_COMPONENT_PIXEL_DEPTH_8BPC ; 
 int /*<<< orphan*/  DP_MSA_COLORIMETRY ; 
 int /*<<< orphan*/  DP_MSA_HSTART ; 
 int /*<<< orphan*/  DP_MSA_HSYNCPOLARITY ; 
 int /*<<< orphan*/  DP_MSA_HSYNCWIDTH ; 
 int /*<<< orphan*/  DP_MSA_HTOTAL ; 
 int /*<<< orphan*/  DP_MSA_HWIDTH ; 
 int /*<<< orphan*/  DP_MSA_MISC ; 
 int /*<<< orphan*/  DP_MSA_MISC0 ; 
 int /*<<< orphan*/  DP_MSA_TIMING_PARAM1 ; 
 int /*<<< orphan*/  DP_MSA_TIMING_PARAM2 ; 
 int /*<<< orphan*/  DP_MSA_TIMING_PARAM3 ; 
 int /*<<< orphan*/  DP_MSA_TIMING_PARAM4 ; 
 int /*<<< orphan*/  DP_MSA_VHEIGHT ; 
 int /*<<< orphan*/  DP_MSA_VSTART ; 
 int /*<<< orphan*/  DP_MSA_VSYNCPOLARITY ; 
 int /*<<< orphan*/  DP_MSA_VSYNCWIDTH ; 
 int /*<<< orphan*/  DP_MSA_VTOTAL ; 
 int /*<<< orphan*/  DP_PIXEL_ENCODING ; 
 int DP_PIXEL_ENCODING_TYPE_RGB444 ; 
 int DP_PIXEL_ENCODING_TYPE_YCBCR420 ; 
 int DP_PIXEL_ENCODING_TYPE_YCBCR422 ; 
 int DP_PIXEL_ENCODING_TYPE_YCBCR444 ; 
 int DP_PIXEL_ENCODING_TYPE_Y_ONLY ; 
 int /*<<< orphan*/  DP_PIXEL_FORMAT ; 
 int /*<<< orphan*/  DP_VID_N_MUL ; 
 int /*<<< orphan*/  DP_VID_TIMING ; 
#define  PIXEL_ENCODING_YCBCR420 130 
#define  PIXEL_ENCODING_YCBCR422 129 
#define  PIXEL_ENCODING_YCBCR444 128 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 

void enc1_stream_encoder_dp_set_stream_attribute(
	struct stream_encoder *enc,
	struct dc_crtc_timing *crtc_timing,
	enum dc_color_space output_color_space)
{
	uint32_t h_active_start;
	uint32_t v_active_start;
	uint32_t misc0 = 0;
	uint32_t misc1 = 0;
	uint32_t h_blank;
	uint32_t h_back_porch;
	uint8_t synchronous_clock = 0; /* asynchronous mode */
	uint8_t colorimetry_bpc;
	uint8_t dynamic_range_rgb = 0; /*full range*/
	uint8_t dynamic_range_ycbcr = 1; /*bt709*/
	uint8_t dp_pixel_encoding = 0;
	uint8_t dp_component_depth = 0;

	struct dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* set pixel encoding */
	switch (crtc_timing->pixel_encoding) {
	case PIXEL_ENCODING_YCBCR422:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_YCBCR422;
		break;
	case PIXEL_ENCODING_YCBCR444:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_YCBCR444;

		if (crtc_timing->flags.Y_ONLY)
			if (crtc_timing->display_color_depth != COLOR_DEPTH_666)
				/* HW testing only, no use case yet.
				 * Color depth of Y-only could be
				 * 8, 10, 12, 16 bits
				 */
				dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_Y_ONLY;

		/* Note: DP_MSA_MISC1 bit 7 is the indicator
		 * of Y-only mode.
		 * This bit is set in HW if register
		 * DP_PIXEL_ENCODING is programmed to 0x4
		 */
		break;
	case PIXEL_ENCODING_YCBCR420:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_YCBCR420;
		REG_UPDATE(DP_VID_TIMING, DP_VID_N_MUL, 1);
		break;
	default:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_RGB444;
		break;
	}

	misc1 = REG_READ(DP_MSA_MISC);
	/* For YCbCr420 and BT2020 Colorimetry Formats, VSC SDP shall be used.
	 * When MISC1, bit 6, is Set to 1, a Source device uses a VSC SDP to indicate the
	 * Pixel Encoding/Colorimetry Format and that a Sink device shall ignore MISC1, bit 7,
	 * and MISC0, bits 7:1 (MISC1, bit 7, and MISC0, bits 7:1, become "don't care").
	 */
	if ((crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420) ||
			(output_color_space == COLOR_SPACE_2020_YCBCR) ||
			(output_color_space == COLOR_SPACE_2020_RGB_FULLRANGE) ||
			(output_color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE))
		misc1 = misc1 | 0x40;
	else
		misc1 = misc1 & ~0x40;

	/* set color depth */
	switch (crtc_timing->display_color_depth) {
	case COLOR_DEPTH_666:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_6BPC;
		break;
	case COLOR_DEPTH_888:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_8BPC;
		break;
	case COLOR_DEPTH_101010:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_10BPC;
		break;
	case COLOR_DEPTH_121212:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_12BPC;
		break;
	case COLOR_DEPTH_161616:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_16BPC;
		break;
	default:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_6BPC;
		break;
	}

	/* Set DP pixel encoding and component depth */
	REG_UPDATE_2(DP_PIXEL_FORMAT,
			DP_PIXEL_ENCODING, dp_pixel_encoding,
			DP_COMPONENT_DEPTH, dp_component_depth);

	/* set dynamic range and YCbCr range */

	switch (crtc_timing->display_color_depth) {
	case COLOR_DEPTH_666:
		colorimetry_bpc = 0;
		break;
	case COLOR_DEPTH_888:
		colorimetry_bpc = 1;
		break;
	case COLOR_DEPTH_101010:
		colorimetry_bpc = 2;
		break;
	case COLOR_DEPTH_121212:
		colorimetry_bpc = 3;
		break;
	default:
		colorimetry_bpc = 0;
		break;
	}

	misc0 = misc0 | synchronous_clock;
	misc0 = colorimetry_bpc << 5;

	switch (output_color_space) {
	case COLOR_SPACE_SRGB:
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_rgb = 0; /*full range*/
		break;
	case COLOR_SPACE_SRGB_LIMITED:
		misc0 = misc0 | 0x8; /* bit3=1 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_rgb = 1; /*limited range*/
		break;
	case COLOR_SPACE_YCBCR601:
	case COLOR_SPACE_YCBCR601_LIMITED:
		misc0 = misc0 | 0x8; /* bit3=1, bit4=0 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_ycbcr = 0; /*bt601*/
		if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR422)
			misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
		else if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR444)
			misc0 = misc0 | 0x4; /* bit2=1, bit1=0 */
		break;
	case COLOR_SPACE_YCBCR709:
	case COLOR_SPACE_YCBCR709_LIMITED:
		misc0 = misc0 | 0x18; /* bit3=1, bit4=1 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_ycbcr = 1; /*bt709*/
		if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR422)
			misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
		else if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR444)
			misc0 = misc0 | 0x4; /* bit2=1, bit1=0 */
		break;
	case COLOR_SPACE_2020_RGB_LIMITEDRANGE:
		dynamic_range_rgb = 1; /*limited range*/
		break;
	case COLOR_SPACE_2020_RGB_FULLRANGE:
	case COLOR_SPACE_2020_YCBCR:
	case COLOR_SPACE_XR_RGB:
	case COLOR_SPACE_MSREF_SCRGB:
	case COLOR_SPACE_ADOBERGB:
	case COLOR_SPACE_DCIP3:
	case COLOR_SPACE_XV_YCC_709:
	case COLOR_SPACE_XV_YCC_601:
	case COLOR_SPACE_DISPLAYNATIVE:
	case COLOR_SPACE_DOLBYVISION:
	case COLOR_SPACE_APPCTRL:
	case COLOR_SPACE_CUSTOMPOINTS:
	case COLOR_SPACE_UNKNOWN:
		/* do nothing */
		break;
	}

	REG_SET(DP_MSA_COLORIMETRY, 0, DP_MSA_MISC0, misc0);
	REG_WRITE(DP_MSA_MISC, misc1);   /* MSA_MISC1 */

	/* dcn new register
	 * dc_crtc_timing is vesa dmt struct. data from edid
	 */
	REG_SET_2(DP_MSA_TIMING_PARAM1, 0,
			DP_MSA_HTOTAL, crtc_timing->h_total,
			DP_MSA_VTOTAL, crtc_timing->v_total);

	/* calculate from vesa timing parameters
	 * h_active_start related to leading edge of sync
	 */

	h_blank = crtc_timing->h_total - crtc_timing->h_border_left -
			crtc_timing->h_addressable - crtc_timing->h_border_right;

	h_back_porch = h_blank - crtc_timing->h_front_porch -
			crtc_timing->h_sync_width;

	/* start at beginning of left border */
	h_active_start = crtc_timing->h_sync_width + h_back_porch;


	v_active_start = crtc_timing->v_total - crtc_timing->v_border_top -
			crtc_timing->v_addressable - crtc_timing->v_border_bottom -
			crtc_timing->v_front_porch;


	/* start at beginning of left border */
	REG_SET_2(DP_MSA_TIMING_PARAM2, 0,
		DP_MSA_HSTART, h_active_start,
		DP_MSA_VSTART, v_active_start);

	REG_SET_4(DP_MSA_TIMING_PARAM3, 0,
			DP_MSA_HSYNCWIDTH,
			crtc_timing->h_sync_width,
			DP_MSA_HSYNCPOLARITY,
			!crtc_timing->flags.HSYNC_POSITIVE_POLARITY,
			DP_MSA_VSYNCWIDTH,
			crtc_timing->v_sync_width,
			DP_MSA_VSYNCPOLARITY,
			!crtc_timing->flags.VSYNC_POSITIVE_POLARITY);

	/* HWDITH include border or overscan */
	REG_SET_2(DP_MSA_TIMING_PARAM4, 0,
		DP_MSA_HWIDTH, crtc_timing->h_border_left +
		crtc_timing->h_addressable + crtc_timing->h_border_right,
		DP_MSA_VHEIGHT, crtc_timing->v_border_top +
		crtc_timing->v_addressable + crtc_timing->v_border_bottom);
}