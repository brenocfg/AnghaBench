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
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  vpx3220_fp_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpx3220_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpx3220_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		vpx3220_write(sd, 0xe6, ctrl->val);
		return 0;
	case V4L2_CID_CONTRAST:
		/* Bit 7 and 8 is for noise shaping */
		vpx3220_write(sd, 0xe7, ctrl->val + 192);
		return 0;
	case V4L2_CID_SATURATION:
		vpx3220_fp_write(sd, 0xa0, ctrl->val);
		return 0;
	case V4L2_CID_HUE:
		vpx3220_fp_write(sd, 0x1c, ctrl->val);
		return 0;
	}
	return -EINVAL;
}