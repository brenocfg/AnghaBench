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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7393_DAC123_OUTPUT_LEVEL ; 
 int ADV7393_HUE_MIN ; 
 int /*<<< orphan*/  ADV7393_SD_BRIGHTNESS_WSS ; 
 int /*<<< orphan*/  ADV7393_SD_HUE_ADJUST ; 
 int EINVAL ; 
 int SD_BRIGHTNESS_VALUE_MASK ; 
#define  V4L2_CID_BRIGHTNESS 130 
#define  V4L2_CID_GAIN 129 
#define  V4L2_CID_HUE 128 
 int adv7393_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 

__attribute__((used)) static int adv7393_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		return adv7393_write(sd, ADV7393_SD_BRIGHTNESS_WSS,
					ctrl->val & SD_BRIGHTNESS_VALUE_MASK);

	case V4L2_CID_HUE:
		return adv7393_write(sd, ADV7393_SD_HUE_ADJUST,
					ctrl->val - ADV7393_HUE_MIN);

	case V4L2_CID_GAIN:
		return adv7393_write(sd, ADV7393_DAC123_OUTPUT_LEVEL,
					ctrl->val);
	}
	return -EINVAL;
}