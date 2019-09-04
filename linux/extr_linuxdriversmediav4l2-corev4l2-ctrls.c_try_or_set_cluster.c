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
typedef  int u32 ;
struct v4l2_fh {int dummy; } ;
struct v4l2_ctrl {int ncontrols; int flags; int has_changed; struct v4l2_ctrl** cluster; scalar_t__ has_volatiles; int /*<<< orphan*/  is_new; } ;

/* Variables and functions */
 int EBUSY ; 
 int V4L2_CTRL_FLAG_GRABBED ; 
 int V4L2_EVENT_CTRL_CH_FLAGS ; 
 int call_op (struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_changed (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  cur_to_new (struct v4l2_ctrl*) ; 
 scalar_t__ is_cur_manual (struct v4l2_ctrl*) ; 
 scalar_t__ is_new_manual (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  new_to_cur (struct v4l2_fh*,struct v4l2_ctrl*,int) ; 
 int /*<<< orphan*/  s_ctrl ; 
 int /*<<< orphan*/  try_ctrl ; 

__attribute__((used)) static int try_or_set_cluster(struct v4l2_fh *fh, struct v4l2_ctrl *master,
			      bool set, u32 ch_flags)
{
	bool update_flag;
	int ret;
	int i;

	/* Go through the cluster and either validate the new value or
	   (if no new value was set), copy the current value to the new
	   value, ensuring a consistent view for the control ops when
	   called. */
	for (i = 0; i < master->ncontrols; i++) {
		struct v4l2_ctrl *ctrl = master->cluster[i];

		if (ctrl == NULL)
			continue;

		if (!ctrl->is_new) {
			cur_to_new(ctrl);
			continue;
		}
		/* Check again: it may have changed since the
		   previous check in try_or_set_ext_ctrls(). */
		if (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED))
			return -EBUSY;
	}

	ret = call_op(master, try_ctrl);

	/* Don't set if there is no change */
	if (ret || !set || !cluster_changed(master))
		return ret;
	ret = call_op(master, s_ctrl);
	if (ret)
		return ret;

	/* If OK, then make the new values permanent. */
	update_flag = is_cur_manual(master) != is_new_manual(master);

	for (i = 0; i < master->ncontrols; i++) {
		/*
		 * If we switch from auto to manual mode, and this cluster
		 * contains volatile controls, then all non-master controls
		 * have to be marked as changed. The 'new' value contains
		 * the volatile value (obtained by update_from_auto_cluster),
		 * which now has to become the current value.
		 */
		if (i && update_flag && is_new_manual(master) &&
		    master->has_volatiles && master->cluster[i])
			master->cluster[i]->has_changed = true;

		new_to_cur(fh, master->cluster[i], ch_flags |
			((update_flag && i > 0) ? V4L2_EVENT_CTRL_CH_FLAGS : 0));
	}
	return 0;
}