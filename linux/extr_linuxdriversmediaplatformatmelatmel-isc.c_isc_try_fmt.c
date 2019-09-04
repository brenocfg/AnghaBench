#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct isc_format {int bpp; int /*<<< orphan*/  mbus_code; int /*<<< orphan*/  fourcc; } ;
struct isc_device {int num_user_formats; TYPE_3__* current_subdev; TYPE_2__* raw_fmt; struct isc_format** user_formats; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  sd; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int EINVAL ; 
 int ISC_MAX_SUPPORT_HEIGHT ; 
 int ISC_MAX_SUPPORT_WIDTH ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct isc_format* find_format_by_fourcc (struct isc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 scalar_t__ sensor_is_preferred (struct isc_format*) ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isc_try_fmt(struct isc_device *isc, struct v4l2_format *f,
			struct isc_format **current_fmt, u32 *code)
{
	struct isc_format *isc_fmt;
	struct v4l2_pix_format *pixfmt = &f->fmt.pix;
	struct v4l2_subdev_pad_config pad_cfg;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_TRY,
	};
	u32 mbus_code;
	int ret;

	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	isc_fmt = find_format_by_fourcc(isc, pixfmt->pixelformat);
	if (!isc_fmt) {
		v4l2_warn(&isc->v4l2_dev, "Format 0x%x not found\n",
			  pixfmt->pixelformat);
		isc_fmt = isc->user_formats[isc->num_user_formats - 1];
		pixfmt->pixelformat = isc_fmt->fourcc;
	}

	/* Limit to Atmel ISC hardware capabilities */
	if (pixfmt->width > ISC_MAX_SUPPORT_WIDTH)
		pixfmt->width = ISC_MAX_SUPPORT_WIDTH;
	if (pixfmt->height > ISC_MAX_SUPPORT_HEIGHT)
		pixfmt->height = ISC_MAX_SUPPORT_HEIGHT;

	if (sensor_is_preferred(isc_fmt))
		mbus_code = isc_fmt->mbus_code;
	else
		mbus_code = isc->raw_fmt->mbus_code;

	v4l2_fill_mbus_format(&format.format, pixfmt, mbus_code);
	ret = v4l2_subdev_call(isc->current_subdev->sd, pad, set_fmt,
			       &pad_cfg, &format);
	if (ret < 0)
		return ret;

	v4l2_fill_pix_format(pixfmt, &format.format);

	pixfmt->field = V4L2_FIELD_NONE;
	pixfmt->bytesperline = (pixfmt->width * isc_fmt->bpp) >> 3;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	if (current_fmt)
		*current_fmt = isc_fmt;

	if (code)
		*code = mbus_code;

	return 0;
}