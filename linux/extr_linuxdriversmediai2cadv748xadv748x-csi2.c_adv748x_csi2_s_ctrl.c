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
struct v4l2_ctrl {int id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_PIXEL_RATE 128 

__attribute__((used)) static int adv748x_csi2_s_ctrl(struct v4l2_ctrl *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_PIXEL_RATE:
		return 0;
	default:
		return -EINVAL;
	}
}