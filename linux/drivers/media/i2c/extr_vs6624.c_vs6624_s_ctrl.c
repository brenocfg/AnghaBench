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
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HFLIP 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_VFLIP 128 
 int /*<<< orphan*/  VS6624_CONTRAST0 ; 
 int /*<<< orphan*/  VS6624_HMIRROR0 ; 
 int /*<<< orphan*/  VS6624_SATURATION0 ; 
 int /*<<< orphan*/  VS6624_VFLIP0 ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  vs6624_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vs6624_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_CONTRAST:
		vs6624_write(sd, VS6624_CONTRAST0, ctrl->val);
		break;
	case V4L2_CID_SATURATION:
		vs6624_write(sd, VS6624_SATURATION0, ctrl->val);
		break;
	case V4L2_CID_HFLIP:
		vs6624_write(sd, VS6624_HMIRROR0, ctrl->val);
		break;
	case V4L2_CID_VFLIP:
		vs6624_write(sd, VS6624_VFLIP0, ctrl->val);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}