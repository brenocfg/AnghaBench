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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV8_2X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  ov9740_res_roundup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ov9740_s_fmt (struct v4l2_subdev*,struct v4l2_mbus_framefmt*) ; 

__attribute__((used)) static int ov9740_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;

	if (format->pad)
		return -EINVAL;

	ov9740_res_roundup(&mf->width, &mf->height);

	mf->field = V4L2_FIELD_NONE;
	mf->code = MEDIA_BUS_FMT_YUYV8_2X8;
	mf->colorspace = V4L2_COLORSPACE_SRGB;

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return ov9740_s_fmt(sd, mf);
	cfg->try_fmt = *mf;
	return 0;
}