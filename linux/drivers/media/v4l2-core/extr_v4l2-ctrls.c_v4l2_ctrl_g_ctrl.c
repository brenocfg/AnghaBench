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
struct v4l2_ext_control {scalar_t__ value; } ;
struct v4l2_ctrl {int /*<<< orphan*/  is_int; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  get_ctrl (struct v4l2_ctrl*,struct v4l2_ext_control*) ; 

s32 v4l2_ctrl_g_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_ext_control c;

	/* It's a driver bug if this happens. */
	WARN_ON(!ctrl->is_int);
	c.value = 0;
	get_ctrl(ctrl, &c);
	return c.value;
}