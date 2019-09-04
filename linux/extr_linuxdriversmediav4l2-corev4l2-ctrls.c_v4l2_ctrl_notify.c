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
typedef  int /*<<< orphan*/ * v4l2_ctrl_notify_fnc ;
struct v4l2_ctrl {int call_notify; TYPE_1__* handler; } ;
struct TYPE_2__ {void* notify_priv; int /*<<< orphan*/ * notify; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 

void v4l2_ctrl_notify(struct v4l2_ctrl *ctrl, v4l2_ctrl_notify_fnc notify, void *priv)
{
	if (ctrl == NULL)
		return;
	if (notify == NULL) {
		ctrl->call_notify = 0;
		return;
	}
	if (WARN_ON(ctrl->handler->notify && ctrl->handler->notify != notify))
		return;
	ctrl->handler->notify = notify;
	ctrl->handler->notify_priv = priv;
	ctrl->call_notify = 1;
}