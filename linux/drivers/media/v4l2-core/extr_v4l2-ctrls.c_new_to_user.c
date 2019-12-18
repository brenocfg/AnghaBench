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
struct v4l2_ext_control {int dummy; } ;
struct v4l2_ctrl {int /*<<< orphan*/  p_new; } ;

/* Variables and functions */
 int ptr_to_user (struct v4l2_ext_control*,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int new_to_user(struct v4l2_ext_control *c,
		       struct v4l2_ctrl *ctrl)
{
	return ptr_to_user(c, ctrl, ctrl->p_new);
}