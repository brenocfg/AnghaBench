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
typedef  int u32 ;
struct v4l2_fh {int dummy; } ;
struct v4l2_ctrl {int has_changed; int flags; TYPE_1__* handler; scalar_t__ call_notify; int /*<<< orphan*/  is_new; TYPE_2__** cluster; int /*<<< orphan*/  p_cur; int /*<<< orphan*/  p_new; } ;
struct TYPE_4__ {scalar_t__ has_volatiles; } ;
struct TYPE_3__ {int /*<<< orphan*/  notify_priv; int /*<<< orphan*/  (* notify ) (struct v4l2_ctrl*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int V4L2_CTRL_FLAG_INACTIVE ; 
 int V4L2_CTRL_FLAG_VOLATILE ; 
 int V4L2_EVENT_CTRL_CH_FLAGS ; 
 int V4L2_EVENT_CTRL_CH_VALUE ; 
 int /*<<< orphan*/  is_cur_manual (TYPE_2__*) ; 
 int /*<<< orphan*/  ptr_to_ptr (struct v4l2_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_event (struct v4l2_fh*,struct v4l2_ctrl*,int) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_to_cur(struct v4l2_fh *fh, struct v4l2_ctrl *ctrl, u32 ch_flags)
{
	bool changed;

	if (ctrl == NULL)
		return;

	/* has_changed is set by cluster_changed */
	changed = ctrl->has_changed;
	if (changed)
		ptr_to_ptr(ctrl, ctrl->p_new, ctrl->p_cur);

	if (ch_flags & V4L2_EVENT_CTRL_CH_FLAGS) {
		/* Note: CH_FLAGS is only set for auto clusters. */
		ctrl->flags &=
			~(V4L2_CTRL_FLAG_INACTIVE | V4L2_CTRL_FLAG_VOLATILE);
		if (!is_cur_manual(ctrl->cluster[0])) {
			ctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
			if (ctrl->cluster[0]->has_volatiles)
				ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
		}
		fh = NULL;
	}
	if (changed || ch_flags) {
		/* If a control was changed that was not one of the controls
		   modified by the application, then send the event to all. */
		if (!ctrl->is_new)
			fh = NULL;
		send_event(fh, ctrl,
			(changed ? V4L2_EVENT_CTRL_CH_VALUE : 0) | ch_flags);
		if (ctrl->call_notify && changed && ctrl->handler->notify)
			ctrl->handler->notify(ctrl, ctrl->handler->notify_priv);
	}
}