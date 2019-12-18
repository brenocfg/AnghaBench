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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {scalar_t__ pad; scalar_t__ which; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADV748X_HDMI_SOURCE ; 
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int adv748x_hdmi_get_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

__attribute__((used)) static int adv748x_hdmi_set_format(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_format *sdformat)
{
	struct v4l2_mbus_framefmt *mbusformat;

	if (sdformat->pad != ADV748X_HDMI_SOURCE)
		return -EINVAL;

	if (sdformat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return adv748x_hdmi_get_format(sd, cfg, sdformat);

	mbusformat = v4l2_subdev_get_try_format(sd, cfg, sdformat->pad);
	*mbusformat = sdformat->format;

	return 0;
}