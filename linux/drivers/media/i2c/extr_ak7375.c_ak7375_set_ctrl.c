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
struct ak7375_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK7375_REG_POSITION ; 
 int EINVAL ; 
 scalar_t__ V4L2_CID_FOCUS_ABSOLUTE ; 
 int ak7375_i2c_write (struct ak7375_device*,int /*<<< orphan*/ ,int,int) ; 
 struct ak7375_device* to_ak7375_vcm (struct v4l2_ctrl*) ; 

__attribute__((used)) static int ak7375_set_ctrl(struct v4l2_ctrl *ctrl)
{
	struct ak7375_device *dev_vcm = to_ak7375_vcm(ctrl);

	if (ctrl->id == V4L2_CID_FOCUS_ABSOLUTE)
		return ak7375_i2c_write(dev_vcm, AK7375_REG_POSITION,
					ctrl->val << 4, 2);

	return -EINVAL;
}