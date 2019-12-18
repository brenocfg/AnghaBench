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
struct v4l2_mbus_framefmt {int code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE 130 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 129 
#define  MEDIA_BUS_FMT_UYVY8_2X8 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  ov9640_res_roundup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ov9640_s_fmt (struct v4l2_subdev*,struct v4l2_mbus_framefmt*) ; 

__attribute__((used)) static int ov9640_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;

	if (format->pad)
		return -EINVAL;

	ov9640_res_roundup(&mf->width, &mf->height);

	mf->field = V4L2_FIELD_NONE;

	switch (mf->code) {
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
		mf->colorspace = V4L2_COLORSPACE_SRGB;
		break;
	default:
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		/* fall through */
	case MEDIA_BUS_FMT_UYVY8_2X8:
		mf->colorspace = V4L2_COLORSPACE_JPEG;
		break;
	}

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return ov9640_s_fmt(sd, mf);

	cfg->try_fmt = *mf;

	return 0;
}