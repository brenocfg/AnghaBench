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
struct TYPE_2__ {unsigned int width; unsigned int height; } ;
struct v4l2_subdev_selection {TYPE_1__ r; int /*<<< orphan*/  target; int /*<<< orphan*/  which; } ;
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_rect {int dummy; } ;
struct soc_camera_device {struct device* parent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP_BOUNDS ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_geo (struct device*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  get_selection ; 
 unsigned int min (int,unsigned int) ; 
 int /*<<< orphan*/  move_and_crop_subrect (struct v4l2_rect*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int soc_camera_client_g_rect (struct v4l2_subdev*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  soc_camera_grp_id (struct soc_camera_device*) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_selection*) ; 

__attribute__((used)) static int client_set_fmt(struct soc_camera_device *icd,
			struct v4l2_rect *rect, struct v4l2_rect *subrect,
			unsigned int max_width, unsigned int max_height,
			struct v4l2_subdev_format *format, bool host_can_scale)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct device *dev = icd->parent;
	struct v4l2_mbus_framefmt *mf = &format->format;
	unsigned int width = mf->width, height = mf->height, tmp_w, tmp_h;
	struct v4l2_subdev_selection sdsel = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP_BOUNDS,
	};
	bool host_1to1;
	int ret;

	ret = v4l2_device_call_until_err(sd->v4l2_dev,
					 soc_camera_grp_id(icd), pad,
					 set_fmt, NULL, format);
	if (ret < 0)
		return ret;

	dev_geo(dev, "camera scaled to %ux%u\n", mf->width, mf->height);

	if (width == mf->width && height == mf->height) {
		/* Perfect! The client has done it all. */
		host_1to1 = true;
		goto update_cache;
	}

	host_1to1 = false;
	if (!host_can_scale)
		goto update_cache;

	ret = v4l2_subdev_call(sd, pad, get_selection, NULL, &sdsel);
	if (ret < 0)
		return ret;

	if (max_width > sdsel.r.width)
		max_width = sdsel.r.width;
	if (max_height > sdsel.r.height)
		max_height = sdsel.r.height;

	/* Camera set a format, but geometry is not precise, try to improve */
	tmp_w = mf->width;
	tmp_h = mf->height;

	/* width <= max_width && height <= max_height - guaranteed by try_fmt */
	while ((width > tmp_w || height > tmp_h) &&
	       tmp_w < max_width && tmp_h < max_height) {
		tmp_w = min(2 * tmp_w, max_width);
		tmp_h = min(2 * tmp_h, max_height);
		mf->width = tmp_w;
		mf->height = tmp_h;
		ret = v4l2_device_call_until_err(sd->v4l2_dev,
					soc_camera_grp_id(icd), pad,
					set_fmt, NULL, format);
		dev_geo(dev, "Camera scaled to %ux%u\n",
			mf->width, mf->height);
		if (ret < 0) {
			/* This shouldn't happen */
			dev_err(dev, "Client failed to set format: %d\n", ret);
			return ret;
		}
	}

update_cache:
	/* Update cache */
	ret = soc_camera_client_g_rect(sd, rect);
	if (ret < 0)
		return ret;

	if (host_1to1)
		*subrect = *rect;
	else
		move_and_crop_subrect(rect, subrect);

	return 0;
}