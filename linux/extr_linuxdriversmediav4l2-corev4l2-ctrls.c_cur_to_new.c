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
struct v4l2_ctrl {int /*<<< orphan*/  p_new; int /*<<< orphan*/  p_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptr_to_ptr (struct v4l2_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cur_to_new(struct v4l2_ctrl *ctrl)
{
	if (ctrl == NULL)
		return;
	ptr_to_ptr(ctrl, ctrl->p_cur, ctrl->p_new);
}