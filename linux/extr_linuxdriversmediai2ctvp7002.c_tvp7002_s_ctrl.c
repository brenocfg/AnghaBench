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
 int /*<<< orphan*/  TVP7002_B_FINE_GAIN ; 
 int /*<<< orphan*/  TVP7002_G_FINE_GAIN ; 
 int /*<<< orphan*/  TVP7002_R_FINE_GAIN ; 
#define  V4L2_CID_GAIN 128 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  tvp7002_write_err (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tvp7002_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	int error = 0;

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		tvp7002_write_err(sd, TVP7002_R_FINE_GAIN, ctrl->val, &error);
		tvp7002_write_err(sd, TVP7002_G_FINE_GAIN, ctrl->val, &error);
		tvp7002_write_err(sd, TVP7002_B_FINE_GAIN, ctrl->val, &error);
		return error;
	}
	return -EINVAL;
}