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
struct v4l2_mbus_framefmt {int colorspace; scalar_t__ xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  quantization; int /*<<< orphan*/  code; } ;
struct imx_media_pixfmt {scalar_t__ cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 scalar_t__ IPUV3_COLORSPACE_RGB ; 
#define  V4L2_COLORSPACE_BT2020 135 
#define  V4L2_COLORSPACE_DCI_P3 134 
#define  V4L2_COLORSPACE_JPEG 133 
#define  V4L2_COLORSPACE_OPRGB 132 
#define  V4L2_COLORSPACE_RAW 131 
#define  V4L2_COLORSPACE_REC709 130 
#define  V4L2_COLORSPACE_SMPTE170M 129 
#define  V4L2_COLORSPACE_SRGB 128 
 int /*<<< orphan*/  V4L2_MAP_QUANTIZATION_DEFAULT (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_MAP_XFER_FUNC_DEFAULT (int) ; 
 int /*<<< orphan*/  V4L2_MAP_YCBCR_ENC_DEFAULT (int) ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 scalar_t__ V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_601 ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_709 ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 struct imx_media_pixfmt* imx_media_find_ipu_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx_media_pixfmt* imx_media_find_mbus_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void imx_media_try_colorimetry(struct v4l2_mbus_framefmt *tryfmt,
			       bool ic_route)
{
	const struct imx_media_pixfmt *cc;
	bool is_rgb = false;

	cc = imx_media_find_mbus_format(tryfmt->code, CS_SEL_ANY, true);
	if (!cc)
		cc = imx_media_find_ipu_format(tryfmt->code, CS_SEL_ANY);
	if (cc && cc->cs == IPUV3_COLORSPACE_RGB)
		is_rgb = true;

	switch (tryfmt->colorspace) {
	case V4L2_COLORSPACE_SMPTE170M:
	case V4L2_COLORSPACE_REC709:
	case V4L2_COLORSPACE_JPEG:
	case V4L2_COLORSPACE_SRGB:
	case V4L2_COLORSPACE_BT2020:
	case V4L2_COLORSPACE_OPRGB:
	case V4L2_COLORSPACE_DCI_P3:
	case V4L2_COLORSPACE_RAW:
		break;
	default:
		tryfmt->colorspace = V4L2_COLORSPACE_SRGB;
		break;
	}

	if (tryfmt->xfer_func == V4L2_XFER_FUNC_DEFAULT)
		tryfmt->xfer_func =
			V4L2_MAP_XFER_FUNC_DEFAULT(tryfmt->colorspace);

	if (ic_route) {
		if (tryfmt->ycbcr_enc != V4L2_YCBCR_ENC_601 &&
		    tryfmt->ycbcr_enc != V4L2_YCBCR_ENC_709)
			tryfmt->ycbcr_enc = V4L2_YCBCR_ENC_601;
	} else {
		if (tryfmt->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT) {
			tryfmt->ycbcr_enc =
				V4L2_MAP_YCBCR_ENC_DEFAULT(tryfmt->colorspace);
		}
	}

	if (tryfmt->quantization == V4L2_QUANTIZATION_DEFAULT)
		tryfmt->quantization =
			V4L2_MAP_QUANTIZATION_DEFAULT(is_rgb,
						      tryfmt->colorspace,
						      tryfmt->ycbcr_enc);
}