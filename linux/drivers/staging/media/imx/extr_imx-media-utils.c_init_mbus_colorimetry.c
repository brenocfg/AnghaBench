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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; } ;
struct imx_media_pixfmt {scalar_t__ cs; } ;

/* Variables and functions */
 scalar_t__ IPUV3_COLORSPACE_RGB ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_MAP_QUANTIZATION_DEFAULT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_XFER_FUNC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_YCBCR_ENC_DEFAULT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_mbus_colorimetry(struct v4l2_mbus_framefmt *mbus,
				  const struct imx_media_pixfmt *fmt)
{
	mbus->colorspace = (fmt->cs == IPUV3_COLORSPACE_RGB) ?
		V4L2_COLORSPACE_SRGB : V4L2_COLORSPACE_SMPTE170M;
	mbus->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(mbus->colorspace);
	mbus->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(mbus->colorspace);
	mbus->quantization =
		V4L2_MAP_QUANTIZATION_DEFAULT(fmt->cs == IPUV3_COLORSPACE_RGB,
					      mbus->colorspace,
					      mbus->ycbcr_enc);
}