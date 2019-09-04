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
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct sr030pc30_info {struct sr030pc30_format const* curr_fmt; } ;
struct sr030pc30_format {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int sr030pc30_set_params (struct v4l2_subdev*) ; 
 struct sr030pc30_info* to_sr030pc30 (struct v4l2_subdev*) ; 
 struct sr030pc30_format* try_fmt (struct v4l2_subdev*,struct v4l2_mbus_framefmt*) ; 

__attribute__((used)) static int sr030pc30_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct sr030pc30_info *info = sd ? to_sr030pc30(sd) : NULL;
	const struct sr030pc30_format *fmt;
	struct v4l2_mbus_framefmt *mf;

	if (!sd || !format)
		return -EINVAL;

	mf = &format->format;
	if (format->pad)
		return -EINVAL;

	fmt = try_fmt(sd, mf);
	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
		cfg->try_fmt = *mf;
		return 0;
	}

	info->curr_fmt = fmt;

	return sr030pc30_set_params(sd);
}