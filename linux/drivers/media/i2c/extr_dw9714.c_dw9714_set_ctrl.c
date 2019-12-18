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
struct v4l2_ctrl {scalar_t__ id; int /*<<< orphan*/  val; } ;
struct dw9714_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_FOCUS_ABSOLUTE ; 
 int dw9714_t_focus_vcm (struct dw9714_device*,int /*<<< orphan*/ ) ; 
 struct dw9714_device* to_dw9714_vcm (struct v4l2_ctrl*) ; 

__attribute__((used)) static int dw9714_set_ctrl(struct v4l2_ctrl *ctrl)
{
	struct dw9714_device *dev_vcm = to_dw9714_vcm(ctrl);

	if (ctrl->id == V4L2_CID_FOCUS_ABSOLUTE)
		return dw9714_t_focus_vcm(dev_vcm, ctrl->val);

	return -EINVAL;
}