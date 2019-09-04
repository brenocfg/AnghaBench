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

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  saa7110_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 

__attribute__((used)) static int saa7110_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		saa7110_write(sd, 0x19, ctrl->val);
		break;
	case V4L2_CID_CONTRAST:
		saa7110_write(sd, 0x13, ctrl->val);
		break;
	case V4L2_CID_SATURATION:
		saa7110_write(sd, 0x12, ctrl->val);
		break;
	case V4L2_CID_HUE:
		saa7110_write(sd, 0x07, ctrl->val);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}