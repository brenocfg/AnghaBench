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
struct v4l2_ctrl {int /*<<< orphan*/  flags; TYPE_1__* handler; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_EVENT_CTRL_CH_FLAGS ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_event (int /*<<< orphan*/ *,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 
 int test_and_clear_bit (int,int /*<<< orphan*/ *) ; 
 int test_and_set_bit (int,int /*<<< orphan*/ *) ; 

void __v4l2_ctrl_grab(struct v4l2_ctrl *ctrl, bool grabbed)
{
	bool old;

	if (ctrl == NULL)
		return;

	lockdep_assert_held(ctrl->handler->lock);

	if (grabbed)
		/* set V4L2_CTRL_FLAG_GRABBED */
		old = test_and_set_bit(1, &ctrl->flags);
	else
		/* clear V4L2_CTRL_FLAG_GRABBED */
		old = test_and_clear_bit(1, &ctrl->flags);
	if (old != grabbed)
		send_event(NULL, ctrl, V4L2_EVENT_CTRL_CH_FLAGS);
}