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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9m001_datafmt {int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct mt9m001 {struct mt9m001_datafmt const* fmt; TYPE_2__ rect; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int mt9m001_set_selection (struct v4l2_subdev*,int /*<<< orphan*/ *,struct v4l2_subdev_selection*) ; 
 struct mt9m001* to_mt9m001 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m001_s_fmt(struct v4l2_subdev *sd,
			 const struct mt9m001_datafmt *fmt,
			 struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m001 *mt9m001 = to_mt9m001(client);
	struct v4l2_subdev_selection sel = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP,
		.r.left = mt9m001->rect.left,
		.r.top = mt9m001->rect.top,
		.r.width = mf->width,
		.r.height = mf->height,
	};
	int ret;

	/* No support for scaling so far, just crop. TODO: use skipping */
	ret = mt9m001_set_selection(sd, NULL, &sel);
	if (!ret) {
		mf->width	= mt9m001->rect.width;
		mf->height	= mt9m001->rect.height;
		mt9m001->fmt	= fmt;
		mf->colorspace	= fmt->colorspace;
	}

	return ret;
}