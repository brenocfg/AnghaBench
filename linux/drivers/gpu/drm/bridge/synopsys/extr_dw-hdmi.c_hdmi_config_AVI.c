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
typedef  int u8 ;
struct hdmi_avi_infoframe {int colorspace; int colorimetry; int extended_colorimetry; int scan_mode; int active_aspect; int top_bar; int bottom_bar; int left_bar; int right_bar; int picture_aspect; int quantization_range; int nups; int video_code; int ycc_quantization_range; int content_type; scalar_t__ itc; } ;
struct TYPE_3__ {int mpixelrepetitioninput; int mpixelrepetitionoutput; } ;
struct TYPE_4__ {int enc_out_encoding; TYPE_1__ video_mode; int /*<<< orphan*/  enc_in_encoding; int /*<<< orphan*/  enc_out_bus_format; } ;
struct dw_hdmi {TYPE_2__ hdmi_data; int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 void* HDMI_COLORIMETRY_EXTENDED ; 
 void* HDMI_COLORIMETRY_ITU_601 ; 
 int HDMI_COLORIMETRY_ITU_709 ; 
 int HDMI_COLORSPACE_RGB ; 
 int HDMI_COLORSPACE_YUV420 ; 
 int HDMI_COLORSPACE_YUV422 ; 
 int HDMI_COLORSPACE_YUV444 ; 
 void* HDMI_EXTENDED_COLORIMETRY_XV_YCC_601 ; 
 int HDMI_EXTENDED_COLORIMETRY_XV_YCC_709 ; 
 int /*<<< orphan*/  HDMI_FC_AVICONF0 ; 
 int HDMI_FC_AVICONF0_ACTIVE_FMT_INFO_PRESENT ; 
 int HDMI_FC_AVICONF0_BAR_DATA_HORIZ_BAR ; 
 int HDMI_FC_AVICONF0_BAR_DATA_VERT_BAR ; 
 int /*<<< orphan*/  HDMI_FC_AVICONF1 ; 
 int /*<<< orphan*/  HDMI_FC_AVICONF2 ; 
 int HDMI_FC_AVICONF2_IT_CONTENT_VALID ; 
 int /*<<< orphan*/  HDMI_FC_AVICONF3 ; 
 int /*<<< orphan*/  HDMI_FC_AVIELB0 ; 
 int /*<<< orphan*/  HDMI_FC_AVIELB1 ; 
 int /*<<< orphan*/  HDMI_FC_AVIETB0 ; 
 int /*<<< orphan*/  HDMI_FC_AVIETB1 ; 
 int /*<<< orphan*/  HDMI_FC_AVISBB0 ; 
 int /*<<< orphan*/  HDMI_FC_AVISBB1 ; 
 int /*<<< orphan*/  HDMI_FC_AVISRB0 ; 
 int /*<<< orphan*/  HDMI_FC_AVISRB1 ; 
 int /*<<< orphan*/  HDMI_FC_AVIVID ; 
 int /*<<< orphan*/  HDMI_FC_PRCONF ; 
 int HDMI_FC_PRCONF_INCOMING_PR_FACTOR_MASK ; 
 int HDMI_FC_PRCONF_INCOMING_PR_FACTOR_OFFSET ; 
 int HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_MASK ; 
 int HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_OFFSET ; 
 int HDMI_SCAN_MODE_NONE ; 
#define  V4L2_YCBCR_ENC_601 129 
#define  V4L2_YCBCR_ENC_709 128 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_XV601 ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_XV709 ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 scalar_t__ hdmi_bus_fmt_is_yuv420 (int /*<<< orphan*/ ) ; 
 scalar_t__ hdmi_bus_fmt_is_yuv422 (int /*<<< orphan*/ ) ; 
 scalar_t__ hdmi_bus_fmt_is_yuv444 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_config_AVI(struct dw_hdmi *hdmi, struct drm_display_mode *mode)
{
	struct hdmi_avi_infoframe frame;
	u8 val;

	/* Initialise info frame from DRM mode */
	drm_hdmi_avi_infoframe_from_display_mode(&frame,
						 &hdmi->connector, mode);

	if (hdmi_bus_fmt_is_yuv444(hdmi->hdmi_data.enc_out_bus_format))
		frame.colorspace = HDMI_COLORSPACE_YUV444;
	else if (hdmi_bus_fmt_is_yuv422(hdmi->hdmi_data.enc_out_bus_format))
		frame.colorspace = HDMI_COLORSPACE_YUV422;
	else if (hdmi_bus_fmt_is_yuv420(hdmi->hdmi_data.enc_out_bus_format))
		frame.colorspace = HDMI_COLORSPACE_YUV420;
	else
		frame.colorspace = HDMI_COLORSPACE_RGB;

	/* Set up colorimetry */
	switch (hdmi->hdmi_data.enc_out_encoding) {
	case V4L2_YCBCR_ENC_601:
		if (hdmi->hdmi_data.enc_in_encoding == V4L2_YCBCR_ENC_XV601)
			frame.colorimetry = HDMI_COLORIMETRY_EXTENDED;
		else
			frame.colorimetry = HDMI_COLORIMETRY_ITU_601;
		frame.extended_colorimetry =
				HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
		break;
	case V4L2_YCBCR_ENC_709:
		if (hdmi->hdmi_data.enc_in_encoding == V4L2_YCBCR_ENC_XV709)
			frame.colorimetry = HDMI_COLORIMETRY_EXTENDED;
		else
			frame.colorimetry = HDMI_COLORIMETRY_ITU_709;
		frame.extended_colorimetry =
				HDMI_EXTENDED_COLORIMETRY_XV_YCC_709;
		break;
	default: /* Carries no data */
		frame.colorimetry = HDMI_COLORIMETRY_ITU_601;
		frame.extended_colorimetry =
				HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
		break;
	}

	frame.scan_mode = HDMI_SCAN_MODE_NONE;

	/*
	 * The Designware IP uses a different byte format from standard
	 * AVI info frames, though generally the bits are in the correct
	 * bytes.
	 */

	/*
	 * AVI data byte 1 differences: Colorspace in bits 0,1 rather than 5,6,
	 * scan info in bits 4,5 rather than 0,1 and active aspect present in
	 * bit 6 rather than 4.
	 */
	val = (frame.scan_mode & 3) << 4 | (frame.colorspace & 3);
	if (frame.active_aspect & 15)
		val |= HDMI_FC_AVICONF0_ACTIVE_FMT_INFO_PRESENT;
	if (frame.top_bar || frame.bottom_bar)
		val |= HDMI_FC_AVICONF0_BAR_DATA_HORIZ_BAR;
	if (frame.left_bar || frame.right_bar)
		val |= HDMI_FC_AVICONF0_BAR_DATA_VERT_BAR;
	hdmi_writeb(hdmi, val, HDMI_FC_AVICONF0);

	/* AVI data byte 2 differences: none */
	val = ((frame.colorimetry & 0x3) << 6) |
	      ((frame.picture_aspect & 0x3) << 4) |
	      (frame.active_aspect & 0xf);
	hdmi_writeb(hdmi, val, HDMI_FC_AVICONF1);

	/* AVI data byte 3 differences: none */
	val = ((frame.extended_colorimetry & 0x7) << 4) |
	      ((frame.quantization_range & 0x3) << 2) |
	      (frame.nups & 0x3);
	if (frame.itc)
		val |= HDMI_FC_AVICONF2_IT_CONTENT_VALID;
	hdmi_writeb(hdmi, val, HDMI_FC_AVICONF2);

	/* AVI data byte 4 differences: none */
	val = frame.video_code & 0x7f;
	hdmi_writeb(hdmi, val, HDMI_FC_AVIVID);

	/* AVI Data Byte 5- set up input and output pixel repetition */
	val = (((hdmi->hdmi_data.video_mode.mpixelrepetitioninput + 1) <<
		HDMI_FC_PRCONF_INCOMING_PR_FACTOR_OFFSET) &
		HDMI_FC_PRCONF_INCOMING_PR_FACTOR_MASK) |
		((hdmi->hdmi_data.video_mode.mpixelrepetitionoutput <<
		HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_OFFSET) &
		HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_MASK);
	hdmi_writeb(hdmi, val, HDMI_FC_PRCONF);

	/*
	 * AVI data byte 5 differences: content type in 0,1 rather than 4,5,
	 * ycc range in bits 2,3 rather than 6,7
	 */
	val = ((frame.ycc_quantization_range & 0x3) << 2) |
	      (frame.content_type & 0x3);
	hdmi_writeb(hdmi, val, HDMI_FC_AVICONF3);

	/* AVI Data Bytes 6-13 */
	hdmi_writeb(hdmi, frame.top_bar & 0xff, HDMI_FC_AVIETB0);
	hdmi_writeb(hdmi, (frame.top_bar >> 8) & 0xff, HDMI_FC_AVIETB1);
	hdmi_writeb(hdmi, frame.bottom_bar & 0xff, HDMI_FC_AVISBB0);
	hdmi_writeb(hdmi, (frame.bottom_bar >> 8) & 0xff, HDMI_FC_AVISBB1);
	hdmi_writeb(hdmi, frame.left_bar & 0xff, HDMI_FC_AVIELB0);
	hdmi_writeb(hdmi, (frame.left_bar >> 8) & 0xff, HDMI_FC_AVIELB1);
	hdmi_writeb(hdmi, frame.right_bar & 0xff, HDMI_FC_AVISRB0);
	hdmi_writeb(hdmi, (frame.right_bar >> 8) & 0xff, HDMI_FC_AVISRB1);
}