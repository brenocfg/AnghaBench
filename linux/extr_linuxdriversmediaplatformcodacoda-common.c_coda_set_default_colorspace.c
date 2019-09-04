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
struct v4l2_pix_format {scalar_t__ pixelformat; int width; int height; int colorspace; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; } ;
typedef  enum v4l2_colorspace { ____Placeholder_v4l2_colorspace } v4l2_colorspace ;

/* Variables and functions */
 int V4L2_COLORSPACE_JPEG ; 
 int V4L2_COLORSPACE_REC709 ; 
 int V4L2_COLORSPACE_SMPTE170M ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 

__attribute__((used)) static void coda_set_default_colorspace(struct v4l2_pix_format *fmt)
{
	enum v4l2_colorspace colorspace;

	if (fmt->pixelformat == V4L2_PIX_FMT_JPEG)
		colorspace = V4L2_COLORSPACE_JPEG;
	else if (fmt->width <= 720 && fmt->height <= 576)
		colorspace = V4L2_COLORSPACE_SMPTE170M;
	else
		colorspace = V4L2_COLORSPACE_REC709;

	fmt->colorspace = colorspace;
	fmt->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	fmt->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	fmt->quantization = V4L2_QUANTIZATION_DEFAULT;
}