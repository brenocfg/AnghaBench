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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct stream_encoder {int dummy; } ;
struct dce110_stream_encoder {TYPE_1__* se_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  VSYNC_POSITIVE_POLARITY; int /*<<< orphan*/  HSYNC_POSITIVE_POLARITY; int /*<<< orphan*/  Y_ONLY; scalar_t__ INTERLACE; } ;
struct dc_crtc_timing {int v_total; int v_border_top; int v_addressable; int v_border_bottom; int v_front_porch; int v_sync_width; int pixel_encoding; int display_color_depth; int h_total; int h_border_left; int h_addressable; int h_border_right; int h_front_porch; int h_sync_width; TYPE_2__ flags; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_3__ {scalar_t__ DP_YCBCR_RANGE; scalar_t__ DP_DYN_RANGE; int /*<<< orphan*/  DP_VID_N_MUL; int /*<<< orphan*/  DP_VID_M_DOUBLE_VALUE_EN; } ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 155 
#define  COLOR_DEPTH_121212 154 
#define  COLOR_DEPTH_666 153 
#define  COLOR_DEPTH_888 152 
#define  COLOR_SPACE_2020_RGB_FULLRANGE 151 
#define  COLOR_SPACE_2020_RGB_LIMITEDRANGE 150 
#define  COLOR_SPACE_2020_YCBCR 149 
#define  COLOR_SPACE_ADOBERGB 148 
#define  COLOR_SPACE_APPCTRL 147 
#define  COLOR_SPACE_CUSTOMPOINTS 146 
#define  COLOR_SPACE_DCIP3 145 
#define  COLOR_SPACE_DISPLAYNATIVE 144 
#define  COLOR_SPACE_DOLBYVISION 143 
#define  COLOR_SPACE_MSREF_SCRGB 142 
#define  COLOR_SPACE_SRGB 141 
#define  COLOR_SPACE_SRGB_LIMITED 140 
#define  COLOR_SPACE_UNKNOWN 139 
#define  COLOR_SPACE_XR_RGB 138 
#define  COLOR_SPACE_XV_YCC_601 137 
#define  COLOR_SPACE_XV_YCC_709 136 
#define  COLOR_SPACE_YCBCR601 135 
#define  COLOR_SPACE_YCBCR601_LIMITED 134 
#define  COLOR_SPACE_YCBCR709 133 
#define  COLOR_SPACE_YCBCR709_BLACK 132 
#define  COLOR_SPACE_YCBCR709_LIMITED 131 
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_COMPONENT_DEPTH ; 
 int DP_COMPONENT_PIXEL_DEPTH_10BPC ; 
 int DP_COMPONENT_PIXEL_DEPTH_12BPC ; 
 int DP_COMPONENT_PIXEL_DEPTH_6BPC ; 
 int DP_COMPONENT_PIXEL_DEPTH_8BPC ; 
 int /*<<< orphan*/  DP_DYN_RANGE ; 
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
 int /*<<< orphan*/  DP_VID_M_DOUBLE_VALUE_EN ; 
 int /*<<< orphan*/  DP_VID_N_MUL ; 
 int /*<<< orphan*/  DP_VID_TIMING ; 
 int /*<<< orphan*/  DP_YCBCR_RANGE ; 
#define  PIXEL_ENCODING_YCBCR420 130 
#define  PIXEL_ENCODING_YCBCR422 129 
#define  PIXEL_ENCODING_YCBCR444 128 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dce110_stream_encoder_dp_set_stream_attribute(
	struct stream_encoder *enc,
	struct dc_crtc_timing *crtc_timing,
	enum dc_color_space output_color_space,
	uint32_t enable_sdp_splitting)
{
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
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
#endif

	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);
	struct dc_crtc_timing hw_crtc_timing = *crtc_timing;
	if (hw_crtc_timing.flags.INTERLACE) {
		/*the input timing is in VESA spec format with Interlace flag =1*/
		hw_crtc_timing.v_total /= 2;
		hw_crtc_timing.v_border_top /= 2;
		hw_crtc_timing.v_addressable /= 2;
		hw_crtc_timing.v_border_bottom /= 2;
		hw_crtc_timing.v_front_porch /= 2;
		hw_crtc_timing.v_sync_width /= 2;
	}
	/* set pixel encoding */
	switch (hw_crtc_timing.pixel_encoding) {
	case PIXEL_ENCODING_YCBCR422:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_PIXEL_ENCODING,
				DP_PIXEL_ENCODING_TYPE_YCBCR422);
		break;
	case PIXEL_ENCODING_YCBCR444:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_PIXEL_ENCODING,
				DP_PIXEL_ENCODING_TYPE_YCBCR444);

		if (hw_crtc_timing.flags.Y_ONLY)
			if (hw_crtc_timing.display_color_depth != COLOR_DEPTH_666)
				/* HW testing only, no use case yet.
				 * Color depth of Y-only could be
				 * 8, 10, 12, 16 bits */
				REG_UPDATE(DP_PIXEL_FORMAT, DP_PIXEL_ENCODING,
						DP_PIXEL_ENCODING_TYPE_Y_ONLY);
		/* Note: DP_MSA_MISC1 bit 7 is the indicator
		 * of Y-only mode.
		 * This bit is set in HW if register
		 * DP_PIXEL_ENCODING is programmed to 0x4 */
		break;
	case PIXEL_ENCODING_YCBCR420:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_PIXEL_ENCODING,
				DP_PIXEL_ENCODING_TYPE_YCBCR420);
		if (enc110->se_mask->DP_VID_M_DOUBLE_VALUE_EN)
			REG_UPDATE(DP_VID_TIMING, DP_VID_M_DOUBLE_VALUE_EN, 1);

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
		if (enc110->se_mask->DP_VID_N_MUL)
			REG_UPDATE(DP_VID_TIMING, DP_VID_N_MUL, 1);
#endif
		break;
	default:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_PIXEL_ENCODING,
				DP_PIXEL_ENCODING_TYPE_RGB444);
		break;
	}

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	if (REG(DP_MSA_MISC))
		misc1 = REG_READ(DP_MSA_MISC);
#endif

	/* set color depth */

	switch (hw_crtc_timing.display_color_depth) {
	case COLOR_DEPTH_666:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_COMPONENT_DEPTH,
				0);
		break;
	case COLOR_DEPTH_888:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_COMPONENT_DEPTH,
				DP_COMPONENT_PIXEL_DEPTH_8BPC);
		break;
	case COLOR_DEPTH_101010:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_COMPONENT_DEPTH,
				DP_COMPONENT_PIXEL_DEPTH_10BPC);

		break;
	case COLOR_DEPTH_121212:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_COMPONENT_DEPTH,
				DP_COMPONENT_PIXEL_DEPTH_12BPC);
		break;
	default:
		REG_UPDATE(DP_PIXEL_FORMAT, DP_COMPONENT_DEPTH,
				DP_COMPONENT_PIXEL_DEPTH_6BPC);
		break;
	}

	/* set dynamic range and YCbCr range */


#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	switch (hw_crtc_timing.display_color_depth) {
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

	if (REG(DP_MSA_TIMING_PARAM1)) {
		switch (output_color_space) {
		case COLOR_SPACE_SRGB:
			misc0 = misc0 | 0x0;
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
			if (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
				misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
			else if (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR444)
				misc0 = misc0 | 0x4; /* bit2=1, bit1=0 */
			break;
		case COLOR_SPACE_YCBCR709:
		case COLOR_SPACE_YCBCR709_LIMITED:
		case COLOR_SPACE_YCBCR709_BLACK:
			misc0 = misc0 | 0x18; /* bit3=1, bit4=1 */
			misc1 = misc1 & ~0x80; /* bit7 = 0*/
			dynamic_range_ycbcr = 1; /*bt709*/
			if (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
				misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
			else if (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR444)
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
		if (enc110->se_mask->DP_DYN_RANGE && enc110->se_mask->DP_YCBCR_RANGE)
			REG_UPDATE_2(
				DP_PIXEL_FORMAT,
				DP_DYN_RANGE, dynamic_range_rgb,
				DP_YCBCR_RANGE, dynamic_range_ycbcr);

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
		if (REG(DP_MSA_COLORIMETRY))
			REG_SET(DP_MSA_COLORIMETRY, 0, DP_MSA_MISC0, misc0);

		if (REG(DP_MSA_MISC))
			REG_WRITE(DP_MSA_MISC, misc1);   /* MSA_MISC1 */

	/* dcn new register
	 * dc_crtc_timing is vesa dmt struct. data from edid
	 */
		if (REG(DP_MSA_TIMING_PARAM1))
			REG_SET_2(DP_MSA_TIMING_PARAM1, 0,
					DP_MSA_HTOTAL, hw_crtc_timing.h_total,
					DP_MSA_VTOTAL, hw_crtc_timing.v_total);
#endif

		/* calcuate from vesa timing parameters
		 * h_active_start related to leading edge of sync
		 */

		h_blank = hw_crtc_timing.h_total - hw_crtc_timing.h_border_left -
				hw_crtc_timing.h_addressable - hw_crtc_timing.h_border_right;

		h_back_porch = h_blank - hw_crtc_timing.h_front_porch -
				hw_crtc_timing.h_sync_width;

		/* start at begining of left border */
		h_active_start = hw_crtc_timing.h_sync_width + h_back_porch;


		v_active_start = hw_crtc_timing.v_total - hw_crtc_timing.v_border_top -
				hw_crtc_timing.v_addressable - hw_crtc_timing.v_border_bottom -
				hw_crtc_timing.v_front_porch;


#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
		/* start at begining of left border */
		if (REG(DP_MSA_TIMING_PARAM2))
			REG_SET_2(DP_MSA_TIMING_PARAM2, 0,
				DP_MSA_HSTART, h_active_start,
				DP_MSA_VSTART, v_active_start);

		if (REG(DP_MSA_TIMING_PARAM3))
			REG_SET_4(DP_MSA_TIMING_PARAM3, 0,
					DP_MSA_HSYNCWIDTH,
					hw_crtc_timing.h_sync_width,
					DP_MSA_HSYNCPOLARITY,
					!hw_crtc_timing.flags.HSYNC_POSITIVE_POLARITY,
					DP_MSA_VSYNCWIDTH,
					hw_crtc_timing.v_sync_width,
					DP_MSA_VSYNCPOLARITY,
					!hw_crtc_timing.flags.VSYNC_POSITIVE_POLARITY);

		/* HWDITH include border or overscan */
		if (REG(DP_MSA_TIMING_PARAM4))
			REG_SET_2(DP_MSA_TIMING_PARAM4, 0,
				DP_MSA_HWIDTH, hw_crtc_timing.h_border_left +
				hw_crtc_timing.h_addressable + hw_crtc_timing.h_border_right,
				DP_MSA_VHEIGHT, hw_crtc_timing.v_border_top +
				hw_crtc_timing.v_addressable + hw_crtc_timing.v_border_bottom);
#endif
	}
#endif
}