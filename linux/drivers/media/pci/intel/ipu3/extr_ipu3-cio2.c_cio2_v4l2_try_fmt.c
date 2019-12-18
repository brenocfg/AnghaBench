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
struct v4l2_pix_format_mplane {scalar_t__ width; int height; int num_planes; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; TYPE_2__* plane_fmt; int /*<<< orphan*/  reserved; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct ipu3_cio2_fmt {int /*<<< orphan*/  fourcc; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int bytesperline; int sizeimage; int /*<<< orphan*/  reserved; } ;

/* Variables and functions */
 int CIO2_IMAGE_MAX_LENGTH ; 
 scalar_t__ CIO2_IMAGE_MAX_WIDTH ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_RAW ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 int cio2_bytesperline (scalar_t__) ; 
 struct ipu3_cio2_fmt* cio2_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipu3_cio2_fmt* formats ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cio2_v4l2_try_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	const struct ipu3_cio2_fmt *fmt;
	struct v4l2_pix_format_mplane *mpix = &f->fmt.pix_mp;

	fmt = cio2_find_format(&mpix->pixelformat, NULL);
	if (!fmt)
		fmt = &formats[0];

	/* Only supports up to 4224x3136 */
	if (mpix->width > CIO2_IMAGE_MAX_WIDTH)
		mpix->width = CIO2_IMAGE_MAX_WIDTH;
	if (mpix->height > CIO2_IMAGE_MAX_LENGTH)
		mpix->height = CIO2_IMAGE_MAX_LENGTH;

	mpix->num_planes = 1;
	mpix->pixelformat = fmt->fourcc;
	mpix->colorspace = V4L2_COLORSPACE_RAW;
	mpix->field = V4L2_FIELD_NONE;
	memset(mpix->reserved, 0, sizeof(mpix->reserved));
	mpix->plane_fmt[0].bytesperline = cio2_bytesperline(mpix->width);
	mpix->plane_fmt[0].sizeimage = mpix->plane_fmt[0].bytesperline *
							mpix->height;
	memset(mpix->plane_fmt[0].reserved, 0,
	       sizeof(mpix->plane_fmt[0].reserved));

	/* use default */
	mpix->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	mpix->quantization = V4L2_QUANTIZATION_DEFAULT;
	mpix->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	return 0;
}