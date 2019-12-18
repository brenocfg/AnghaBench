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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct tvp5150 {int enable; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TVP5150_BRIGHT_CTL ; 
 int /*<<< orphan*/  TVP5150_CONTRAST_CTL ; 
 int /*<<< orphan*/  TVP5150_HUE_CTL ; 
 int /*<<< orphan*/  TVP5150_SATURATION_CTL ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_TEST_PATTERN 128 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_selmux (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct tvp5150 *decoder = to_tvp5150(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		regmap_write(decoder->regmap, TVP5150_BRIGHT_CTL, ctrl->val);
		return 0;
	case V4L2_CID_CONTRAST:
		regmap_write(decoder->regmap, TVP5150_CONTRAST_CTL, ctrl->val);
		return 0;
	case V4L2_CID_SATURATION:
		regmap_write(decoder->regmap, TVP5150_SATURATION_CTL,
			     ctrl->val);
		return 0;
	case V4L2_CID_HUE:
		regmap_write(decoder->regmap, TVP5150_HUE_CTL, ctrl->val);
		return 0;
	case V4L2_CID_TEST_PATTERN:
		decoder->enable = ctrl->val ? false : true;
		tvp5150_selmux(sd);
		return 0;
	}
	return -EINVAL;
}