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
struct v4l2_ctrl {int ncontrols; int flags; int has_changed; unsigned int elems; int /*<<< orphan*/  p_new; int /*<<< orphan*/  p_cur; TYPE_1__* type_ops; struct v4l2_ctrl** cluster; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* equal ) (struct v4l2_ctrl*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int V4L2_CTRL_FLAG_EXECUTE_ON_WRITE ; 
 int V4L2_CTRL_FLAG_VOLATILE ; 
 int /*<<< orphan*/  stub1 (struct v4l2_ctrl*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cluster_changed(struct v4l2_ctrl *master)
{
	bool changed = false;
	unsigned idx;
	int i;

	for (i = 0; i < master->ncontrols; i++) {
		struct v4l2_ctrl *ctrl = master->cluster[i];
		bool ctrl_changed = false;

		if (ctrl == NULL)
			continue;

		if (ctrl->flags & V4L2_CTRL_FLAG_EXECUTE_ON_WRITE)
			changed = ctrl_changed = true;

		/*
		 * Set has_changed to false to avoid generating
		 * the event V4L2_EVENT_CTRL_CH_VALUE
		 */
		if (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE) {
			ctrl->has_changed = false;
			continue;
		}

		for (idx = 0; !ctrl_changed && idx < ctrl->elems; idx++)
			ctrl_changed = !ctrl->type_ops->equal(ctrl, idx,
				ctrl->p_cur, ctrl->p_new);
		ctrl->has_changed = ctrl_changed;
		changed |= ctrl->has_changed;
	}
	return changed;
}