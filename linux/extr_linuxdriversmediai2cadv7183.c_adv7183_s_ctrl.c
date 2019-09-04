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
struct v4l2_ctrl {int val; int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7183_BRIGHTNESS ; 
 int /*<<< orphan*/  ADV7183_CONTRAST ; 
 int /*<<< orphan*/  ADV7183_SD_OFFSET_CB ; 
 int /*<<< orphan*/  ADV7183_SD_OFFSET_CR ; 
 int /*<<< orphan*/  ADV7183_SD_SATURATION_CB ; 
 int /*<<< orphan*/  ADV7183_SD_SATURATION_CR ; 
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  adv7183_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 

__attribute__((used)) static int adv7183_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	int val = ctrl->val;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		if (val < 0)
			val = 127 - val;
		adv7183_write(sd, ADV7183_BRIGHTNESS, val);
		break;
	case V4L2_CID_CONTRAST:
		adv7183_write(sd, ADV7183_CONTRAST, val);
		break;
	case V4L2_CID_SATURATION:
		adv7183_write(sd, ADV7183_SD_SATURATION_CB, val >> 8);
		adv7183_write(sd, ADV7183_SD_SATURATION_CR, (val & 0xFF));
		break;
	case V4L2_CID_HUE:
		adv7183_write(sd, ADV7183_SD_OFFSET_CB, val >> 8);
		adv7183_write(sd, ADV7183_SD_OFFSET_CR, (val & 0xFF));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}