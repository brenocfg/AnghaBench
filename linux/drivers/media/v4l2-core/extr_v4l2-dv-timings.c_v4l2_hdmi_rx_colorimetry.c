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
struct v4l2_hdmi_colorimetry {void* xfer_func; void* ycbcr_enc; void* colorspace; void* quantization; void* member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; void* member_0; } ;
struct hdmi_vendor_infoframe {scalar_t__ vic; } ;
struct hdmi_avi_infoframe {int video_code; int colorspace; int /*<<< orphan*/  extended_colorimetry; int /*<<< orphan*/  colorimetry; int /*<<< orphan*/  quantization_range; } ;

/* Variables and functions */
#define  HDMI_COLORIMETRY_EXTENDED 141 
#define  HDMI_COLORIMETRY_ITU_601 140 
#define  HDMI_COLORIMETRY_ITU_709 139 
#define  HDMI_COLORIMETRY_NONE 138 
#define  HDMI_COLORSPACE_RGB 137 
#define  HDMI_EXTENDED_COLORIMETRY_BT2020 136 
#define  HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM 135 
#define  HDMI_EXTENDED_COLORIMETRY_OPRGB 134 
#define  HDMI_EXTENDED_COLORIMETRY_OPYCC_601 133 
#define  HDMI_EXTENDED_COLORIMETRY_S_YCC_601 132 
#define  HDMI_EXTENDED_COLORIMETRY_XV_YCC_601 131 
#define  HDMI_EXTENDED_COLORIMETRY_XV_YCC_709 130 
#define  HDMI_QUANTIZATION_RANGE_FULL 129 
#define  HDMI_QUANTIZATION_RANGE_LIMITED 128 
 void* V4L2_COLORSPACE_BT2020 ; 
 void* V4L2_COLORSPACE_OPRGB ; 
 void* V4L2_COLORSPACE_REC709 ; 
 void* V4L2_COLORSPACE_SMPTE170M ; 
 void* V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_FULL_RANGE ; 
 void* V4L2_QUANTIZATION_LIM_RANGE ; 
 void* V4L2_XFER_FUNC_709 ; 
 void* V4L2_XFER_FUNC_OPRGB ; 
 void* V4L2_XFER_FUNC_SRGB ; 
 void* V4L2_YCBCR_ENC_601 ; 
 void* V4L2_YCBCR_ENC_709 ; 
 void* V4L2_YCBCR_ENC_BT2020 ; 
 void* V4L2_YCBCR_ENC_BT2020_CONST_LUM ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 void* V4L2_YCBCR_ENC_XV601 ; 
 void* V4L2_YCBCR_ENC_XV709 ; 

struct v4l2_hdmi_colorimetry
v4l2_hdmi_rx_colorimetry(const struct hdmi_avi_infoframe *avi,
			 const struct hdmi_vendor_infoframe *hdmi,
			 unsigned int height)
{
	struct v4l2_hdmi_colorimetry c = {
		V4L2_COLORSPACE_SRGB,
		V4L2_YCBCR_ENC_DEFAULT,
		V4L2_QUANTIZATION_FULL_RANGE,
		V4L2_XFER_FUNC_SRGB
	};
	bool is_ce = avi->video_code || (hdmi && hdmi->vic);
	bool is_sdtv = height <= 576;
	bool default_is_lim_range_rgb = avi->video_code > 1;

	switch (avi->colorspace) {
	case HDMI_COLORSPACE_RGB:
		/* RGB pixel encoding */
		switch (avi->colorimetry) {
		case HDMI_COLORIMETRY_EXTENDED:
			switch (avi->extended_colorimetry) {
			case HDMI_EXTENDED_COLORIMETRY_OPRGB:
				c.colorspace = V4L2_COLORSPACE_OPRGB;
				c.xfer_func = V4L2_XFER_FUNC_OPRGB;
				break;
			case HDMI_EXTENDED_COLORIMETRY_BT2020:
				c.colorspace = V4L2_COLORSPACE_BT2020;
				c.xfer_func = V4L2_XFER_FUNC_709;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		switch (avi->quantization_range) {
		case HDMI_QUANTIZATION_RANGE_LIMITED:
			c.quantization = V4L2_QUANTIZATION_LIM_RANGE;
			break;
		case HDMI_QUANTIZATION_RANGE_FULL:
			break;
		default:
			if (default_is_lim_range_rgb)
				c.quantization = V4L2_QUANTIZATION_LIM_RANGE;
			break;
		}
		break;

	default:
		/* YCbCr pixel encoding */
		c.quantization = V4L2_QUANTIZATION_LIM_RANGE;
		switch (avi->colorimetry) {
		case HDMI_COLORIMETRY_NONE:
			if (!is_ce)
				break;
			if (is_sdtv) {
				c.colorspace = V4L2_COLORSPACE_SMPTE170M;
				c.ycbcr_enc = V4L2_YCBCR_ENC_601;
			} else {
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_709;
			}
			c.xfer_func = V4L2_XFER_FUNC_709;
			break;
		case HDMI_COLORIMETRY_ITU_601:
			c.colorspace = V4L2_COLORSPACE_SMPTE170M;
			c.ycbcr_enc = V4L2_YCBCR_ENC_601;
			c.xfer_func = V4L2_XFER_FUNC_709;
			break;
		case HDMI_COLORIMETRY_ITU_709:
			c.colorspace = V4L2_COLORSPACE_REC709;
			c.ycbcr_enc = V4L2_YCBCR_ENC_709;
			c.xfer_func = V4L2_XFER_FUNC_709;
			break;
		case HDMI_COLORIMETRY_EXTENDED:
			switch (avi->extended_colorimetry) {
			case HDMI_EXTENDED_COLORIMETRY_XV_YCC_601:
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_XV709;
				c.xfer_func = V4L2_XFER_FUNC_709;
				break;
			case HDMI_EXTENDED_COLORIMETRY_XV_YCC_709:
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_XV601;
				c.xfer_func = V4L2_XFER_FUNC_709;
				break;
			case HDMI_EXTENDED_COLORIMETRY_S_YCC_601:
				c.colorspace = V4L2_COLORSPACE_SRGB;
				c.ycbcr_enc = V4L2_YCBCR_ENC_601;
				c.xfer_func = V4L2_XFER_FUNC_SRGB;
				break;
			case HDMI_EXTENDED_COLORIMETRY_OPYCC_601:
				c.colorspace = V4L2_COLORSPACE_OPRGB;
				c.ycbcr_enc = V4L2_YCBCR_ENC_601;
				c.xfer_func = V4L2_XFER_FUNC_OPRGB;
				break;
			case HDMI_EXTENDED_COLORIMETRY_BT2020:
				c.colorspace = V4L2_COLORSPACE_BT2020;
				c.ycbcr_enc = V4L2_YCBCR_ENC_BT2020;
				c.xfer_func = V4L2_XFER_FUNC_709;
				break;
			case HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM:
				c.colorspace = V4L2_COLORSPACE_BT2020;
				c.ycbcr_enc = V4L2_YCBCR_ENC_BT2020_CONST_LUM;
				c.xfer_func = V4L2_XFER_FUNC_709;
				break;
			default: /* fall back to ITU_709 */
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_709;
				c.xfer_func = V4L2_XFER_FUNC_709;
				break;
			}
			break;
		default:
			break;
		}
		/*
		 * YCC Quantization Range signaling is more-or-less broken,
		 * let's just ignore this.
		 */
		break;
	}
	return c;
}