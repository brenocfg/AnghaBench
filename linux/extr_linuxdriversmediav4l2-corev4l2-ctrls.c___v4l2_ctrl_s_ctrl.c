#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int /*<<< orphan*/  val; int /*<<< orphan*/  is_int; TYPE_1__* handler; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int set_ctrl (int /*<<< orphan*/ *,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 

int __v4l2_ctrl_s_ctrl(struct v4l2_ctrl *ctrl, s32 val)
{
	lockdep_assert_held(ctrl->handler->lock);

	/* It's a driver bug if this happens. */
	WARN_ON(!ctrl->is_int);
	ctrl->val = val;
	return set_ctrl(NULL, ctrl, 0);
}