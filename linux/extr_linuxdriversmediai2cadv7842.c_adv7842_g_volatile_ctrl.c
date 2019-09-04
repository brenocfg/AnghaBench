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
struct v4l2_ctrl {scalar_t__ id; int val; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_DV_RX_IT_CONTENT_TYPE ; 
 int V4L2_DV_IT_CONTENT_TYPE_NO_ITC ; 
 int infoframe_read (struct v4l2_subdev*,int) ; 
 int io_read (struct v4l2_subdev*,int) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 

__attribute__((used)) static int adv7842_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);

	if (ctrl->id == V4L2_CID_DV_RX_IT_CONTENT_TYPE) {
		ctrl->val = V4L2_DV_IT_CONTENT_TYPE_NO_ITC;
		if ((io_read(sd, 0x60) & 1) && (infoframe_read(sd, 0x03) & 0x80))
			ctrl->val = (infoframe_read(sd, 0x05) >> 4) & 3;
		return 0;
	}
	return -EINVAL;
}