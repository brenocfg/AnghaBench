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
struct TYPE_4__ {int /*<<< orphan*/ * p_s64; } ;
struct v4l2_ctrl {scalar_t__ type; TYPE_2__ p_new; scalar_t__ is_ptr; TYPE_1__* handler; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ V4L2_CTRL_TYPE_INTEGER64 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int set_ctrl (int /*<<< orphan*/ *,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 

int __v4l2_ctrl_s_ctrl_int64(struct v4l2_ctrl *ctrl, s64 val)
{
	lockdep_assert_held(ctrl->handler->lock);

	/* It's a driver bug if this happens. */
	WARN_ON(ctrl->is_ptr || ctrl->type != V4L2_CTRL_TYPE_INTEGER64);
	*ctrl->p_new.p_s64 = val;
	return set_ctrl(NULL, ctrl, 0);
}