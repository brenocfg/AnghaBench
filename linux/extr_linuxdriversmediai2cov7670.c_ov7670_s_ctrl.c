#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct ov7670_info {TYPE_4__* exposure; TYPE_3__* gain; TYPE_2__* hue; TYPE_1__* saturation; } ;
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUTOGAIN 135 
#define  V4L2_CID_BRIGHTNESS 134 
#define  V4L2_CID_CONTRAST 133 
#define  V4L2_CID_EXPOSURE_AUTO 132 
#define  V4L2_CID_HFLIP 131 
#define  V4L2_CID_SATURATION 130 
#define  V4L2_CID_TEST_PATTERN 129 
#define  V4L2_CID_VFLIP 128 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 int ov7670_s_autoexp (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_autogain (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_brightness (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_contrast (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_exp (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_gain (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_hflip (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_sat_hue (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov7670_s_test_pattern (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_s_vflip (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct ov7670_info *info = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		return ov7670_s_brightness(sd, ctrl->val);
	case V4L2_CID_CONTRAST:
		return ov7670_s_contrast(sd, ctrl->val);
	case V4L2_CID_SATURATION:
		return ov7670_s_sat_hue(sd,
				info->saturation->val, info->hue->val);
	case V4L2_CID_VFLIP:
		return ov7670_s_vflip(sd, ctrl->val);
	case V4L2_CID_HFLIP:
		return ov7670_s_hflip(sd, ctrl->val);
	case V4L2_CID_AUTOGAIN:
		/* Only set manual gain if auto gain is not explicitly
		   turned on. */
		if (!ctrl->val) {
			/* ov7670_s_gain turns off auto gain */
			return ov7670_s_gain(sd, info->gain->val);
		}
		return ov7670_s_autogain(sd, ctrl->val);
	case V4L2_CID_EXPOSURE_AUTO:
		/* Only set manual exposure if auto exposure is not explicitly
		   turned on. */
		if (ctrl->val == V4L2_EXPOSURE_MANUAL) {
			/* ov7670_s_exp turns off auto exposure */
			return ov7670_s_exp(sd, info->exposure->val);
		}
		return ov7670_s_autoexp(sd, ctrl->val);
	case V4L2_CID_TEST_PATTERN:
		return ov7670_s_test_pattern(sd, ctrl->val);
	}
	return -EINVAL;
}