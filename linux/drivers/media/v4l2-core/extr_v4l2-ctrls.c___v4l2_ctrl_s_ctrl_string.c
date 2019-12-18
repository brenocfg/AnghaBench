#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_char; } ;
struct v4l2_ctrl {scalar_t__ type; scalar_t__ maximum; TYPE_2__ p_new; TYPE_1__* handler; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ V4L2_CTRL_TYPE_STRING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int set_ctrl (int /*<<< orphan*/ *,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

int __v4l2_ctrl_s_ctrl_string(struct v4l2_ctrl *ctrl, const char *s)
{
	lockdep_assert_held(ctrl->handler->lock);

	/* It's a driver bug if this happens. */
	WARN_ON(ctrl->type != V4L2_CTRL_TYPE_STRING);
	strscpy(ctrl->p_new.p_char, s, ctrl->maximum + 1);
	return set_ctrl(NULL, ctrl, 0);
}