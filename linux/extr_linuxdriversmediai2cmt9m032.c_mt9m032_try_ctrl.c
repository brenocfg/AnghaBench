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
struct v4l2_ctrl {scalar_t__ id; int val; } ;

/* Variables and functions */
 scalar_t__ V4L2_CID_GAIN ; 

__attribute__((used)) static int mt9m032_try_ctrl(struct v4l2_ctrl *ctrl)
{
	if (ctrl->id == V4L2_CID_GAIN && ctrl->val >= 63) {
		/* round because of multiplier used for values >= 63 */
		ctrl->val &= ~1;
	}

	return 0;
}