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
struct v4l2_ctrl {int maximum; int minimum; int menu_skip_mask; int /*<<< orphan*/  default_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_ctrl_modify_range (struct v4l2_ctrl*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __v4l2_ctrl_s_ctrl (struct v4l2_ctrl*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (struct v4l2_ctrl*) ; 

__attribute__((used)) static void coda_update_menu_ctrl(struct v4l2_ctrl *ctrl, int value)
{
	if (!ctrl)
		return;

	v4l2_ctrl_lock(ctrl);

	/*
	 * Extend the control range if the parsed stream contains a known but
	 * unsupported value or level.
	 */
	if (value > ctrl->maximum) {
		__v4l2_ctrl_modify_range(ctrl, ctrl->minimum, value,
			ctrl->menu_skip_mask & ~(1 << value),
			ctrl->default_value);
	} else if (value < ctrl->minimum) {
		__v4l2_ctrl_modify_range(ctrl, value, ctrl->maximum,
			ctrl->menu_skip_mask & ~(1 << value),
			ctrl->default_value);
	}

	__v4l2_ctrl_s_ctrl(ctrl, value);

	v4l2_ctrl_unlock(ctrl);
}