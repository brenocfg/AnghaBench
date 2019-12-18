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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {TYPE_1__ r; int /*<<< orphan*/  target; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9v022_datafmt {int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct mt9v022 {struct mt9v022_datafmt const* fmt; TYPE_2__ rect; int /*<<< orphan*/  model; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MEDIA_BUS_FMT_SBGGR10_1X10 131 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 130 
#define  MEDIA_BUS_FMT_Y10_1X10 129 
#define  MEDIA_BUS_FMT_Y8_1X8 128 
 int /*<<< orphan*/  MT9V022IX7ATC ; 
 int /*<<< orphan*/  MT9V022IX7ATM ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int mt9v022_set_selection (struct v4l2_subdev*,int /*<<< orphan*/ *,struct v4l2_subdev_selection*) ; 
 struct mt9v022* to_mt9v022 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v022_s_fmt(struct v4l2_subdev *sd,
			 const struct mt9v022_datafmt *fmt,
			 struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9v022 *mt9v022 = to_mt9v022(client);
	struct v4l2_subdev_selection sel = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP,
		.r.left = mt9v022->rect.left,
		.r.top = mt9v022->rect.top,
		.r.width = mf->width,
		.r.height = mf->height,
	};
	int ret;

	/*
	 * The caller provides a supported format, as verified per call to
	 * .set_fmt(FORMAT_TRY), datawidth is from our supported format list
	 */
	switch (mf->code) {
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_Y10_1X10:
		if (mt9v022->model != MT9V022IX7ATM)
			return -EINVAL;
		break;
	case MEDIA_BUS_FMT_SBGGR8_1X8:
	case MEDIA_BUS_FMT_SBGGR10_1X10:
		if (mt9v022->model != MT9V022IX7ATC)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	/* No support for scaling on this camera, just crop. */
	ret = mt9v022_set_selection(sd, NULL, &sel);
	if (!ret) {
		mf->width	= mt9v022->rect.width;
		mf->height	= mt9v022->rect.height;
		mt9v022->fmt	= fmt;
		mf->colorspace	= fmt->colorspace;
	}

	return ret;
}