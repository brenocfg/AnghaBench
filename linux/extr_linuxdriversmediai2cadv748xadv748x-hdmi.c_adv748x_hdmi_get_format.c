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
struct adv748x_hdmi {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADV748X_HDMI_SOURCE ; 
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  adv748x_hdmi_fill_format (struct adv748x_hdmi*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  adv748x_hdmi_propagate_pixelrate (struct adv748x_hdmi*) ; 
 struct adv748x_hdmi* adv748x_sd_to_hdmi (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

__attribute__((used)) static int adv748x_hdmi_get_format(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_format *sdformat)
{
	struct adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	struct v4l2_mbus_framefmt *mbusformat;

	if (sdformat->pad != ADV748X_HDMI_SOURCE)
		return -EINVAL;

	if (sdformat->which == V4L2_SUBDEV_FORMAT_TRY) {
		mbusformat = v4l2_subdev_get_try_format(sd, cfg, sdformat->pad);
		sdformat->format = *mbusformat;
	} else {
		adv748x_hdmi_fill_format(hdmi, &sdformat->format);
		adv748x_hdmi_propagate_pixelrate(hdmi);
	}

	return 0;
}