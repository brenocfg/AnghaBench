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
struct adv748x_afe {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADV748X_AFE_SOURCE ; 
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  adv748x_afe_fill_format (struct adv748x_afe*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  adv748x_afe_propagate_pixelrate (struct adv748x_afe*) ; 
 struct adv748x_afe* adv748x_sd_to_afe (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

__attribute__((used)) static int adv748x_afe_get_format(struct v4l2_subdev *sd,
				      struct v4l2_subdev_pad_config *cfg,
				      struct v4l2_subdev_format *sdformat)
{
	struct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	struct v4l2_mbus_framefmt *mbusformat;

	/* It makes no sense to get the format of the analog sink pads */
	if (sdformat->pad != ADV748X_AFE_SOURCE)
		return -EINVAL;

	if (sdformat->which == V4L2_SUBDEV_FORMAT_TRY) {
		mbusformat = v4l2_subdev_get_try_format(sd, cfg, sdformat->pad);
		sdformat->format = *mbusformat;
	} else {
		adv748x_afe_fill_format(afe, &sdformat->format);
		adv748x_afe_propagate_pixelrate(afe);
	}

	return 0;
}