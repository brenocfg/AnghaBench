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
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; scalar_t__ field; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct sun6i_video {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WIDTH ; 
 int /*<<< orphan*/  MIN_HEIGHT ; 
 int /*<<< orphan*/  MIN_WIDTH ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_RAW ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  is_pixformat_valid (int /*<<< orphan*/ ) ; 
 int sun6i_csi_get_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * supported_pixformats ; 
 int /*<<< orphan*/  v4l_bound_align_image (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sun6i_video_try_fmt(struct sun6i_video *video,
			       struct v4l2_format *f)
{
	struct v4l2_pix_format *pixfmt = &f->fmt.pix;
	int bpp;

	if (!is_pixformat_valid(pixfmt->pixelformat))
		pixfmt->pixelformat = supported_pixformats[0];

	v4l_bound_align_image(&pixfmt->width, MIN_WIDTH, MAX_WIDTH, 1,
			      &pixfmt->height, MIN_HEIGHT, MAX_WIDTH, 1, 1);

	bpp = sun6i_csi_get_bpp(pixfmt->pixelformat);
	pixfmt->bytesperline = (pixfmt->width * bpp) >> 3;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	if (pixfmt->field == V4L2_FIELD_ANY)
		pixfmt->field = V4L2_FIELD_NONE;

	pixfmt->colorspace = V4L2_COLORSPACE_RAW;
	pixfmt->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	pixfmt->quantization = V4L2_QUANTIZATION_DEFAULT;
	pixfmt->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	return 0;
}