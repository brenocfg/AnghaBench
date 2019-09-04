#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_fh {int dummy; } ;
struct v4l2_ext_controls {unsigned int error_idx; unsigned int count; scalar_t__ which; TYPE_3__* controls; } ;
struct v4l2_ctrl_helper {int next; struct v4l2_ctrl* ctrl; TYPE_1__* mref; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl {unsigned int ncontrols; scalar_t__ manual_mode_value; int /*<<< orphan*/  p_new; scalar_t__ is_ptr; scalar_t__ has_volatiles; scalar_t__ is_auto; TYPE_2__** cluster; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  helper ;
struct TYPE_7__ {scalar_t__ value; } ;
struct TYPE_6__ {scalar_t__ is_new; } ;
struct TYPE_5__ {struct v4l2_ctrl* ctrl; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct v4l2_ctrl_helper*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ V4L2_CTRL_ID2WHICH (scalar_t__) ; 
 scalar_t__ V4L2_CTRL_WHICH_DEF_VAL ; 
 int class_check (struct v4l2_ctrl_handler*,scalar_t__) ; 
 int /*<<< orphan*/  is_cur_manual (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  kvfree (struct v4l2_ctrl_helper*) ; 
 struct v4l2_ctrl_helper* kvmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int new_to_user (TYPE_3__*,struct v4l2_ctrl*) ; 
 int prepare_ext_ctrls (struct v4l2_ctrl_handler*,struct v4l2_ext_controls*,struct v4l2_ctrl_helper*,int) ; 
 int try_or_set_cluster (struct v4l2_fh*,struct v4l2_ctrl*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_from_auto_cluster (struct v4l2_ctrl*) ; 
 int user_to_new (TYPE_3__*,struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (struct v4l2_ctrl*) ; 
 int validate_ctrls (struct v4l2_ext_controls*,struct v4l2_ctrl_helper*,int) ; 
 int validate_new (struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_set_ext_ctrls(struct v4l2_fh *fh, struct v4l2_ctrl_handler *hdl,
			     struct v4l2_ext_controls *cs,
			     bool set)
{
	struct v4l2_ctrl_helper helper[4];
	struct v4l2_ctrl_helper *helpers = helper;
	unsigned i, j;
	int ret;

	cs->error_idx = cs->count;

	/* Default value cannot be changed */
	if (cs->which == V4L2_CTRL_WHICH_DEF_VAL)
		return -EINVAL;

	cs->which = V4L2_CTRL_ID2WHICH(cs->which);

	if (hdl == NULL)
		return -EINVAL;

	if (cs->count == 0)
		return class_check(hdl, cs->which);

	if (cs->count > ARRAY_SIZE(helper)) {
		helpers = kvmalloc_array(cs->count, sizeof(helper[0]),
					 GFP_KERNEL);
		if (!helpers)
			return -ENOMEM;
	}
	ret = prepare_ext_ctrls(hdl, cs, helpers, false);
	if (!ret)
		ret = validate_ctrls(cs, helpers, set);
	if (ret && set)
		cs->error_idx = cs->count;
	for (i = 0; !ret && i < cs->count; i++) {
		struct v4l2_ctrl *master;
		u32 idx = i;

		if (helpers[i].mref == NULL)
			continue;

		cs->error_idx = i;
		master = helpers[i].mref->ctrl;
		v4l2_ctrl_lock(master);

		/* Reset the 'is_new' flags of the cluster */
		for (j = 0; j < master->ncontrols; j++)
			if (master->cluster[j])
				master->cluster[j]->is_new = 0;

		/* For volatile autoclusters that are currently in auto mode
		   we need to discover if it will be set to manual mode.
		   If so, then we have to copy the current volatile values
		   first since those will become the new manual values (which
		   may be overwritten by explicit new values from this set
		   of controls). */
		if (master->is_auto && master->has_volatiles &&
						!is_cur_manual(master)) {
			/* Pick an initial non-manual value */
			s32 new_auto_val = master->manual_mode_value + 1;
			u32 tmp_idx = idx;

			do {
				/* Check if the auto control is part of the
				   list, and remember the new value. */
				if (helpers[tmp_idx].ctrl == master)
					new_auto_val = cs->controls[tmp_idx].value;
				tmp_idx = helpers[tmp_idx].next;
			} while (tmp_idx);
			/* If the new value == the manual value, then copy
			   the current volatile values. */
			if (new_auto_val == master->manual_mode_value)
				update_from_auto_cluster(master);
		}

		/* Copy the new caller-supplied control values.
		   user_to_new() sets 'is_new' to 1. */
		do {
			struct v4l2_ctrl *ctrl = helpers[idx].ctrl;

			ret = user_to_new(cs->controls + idx, ctrl);
			if (!ret && ctrl->is_ptr)
				ret = validate_new(ctrl, ctrl->p_new);
			idx = helpers[idx].next;
		} while (!ret && idx);

		if (!ret)
			ret = try_or_set_cluster(fh, master, set, 0);

		/* Copy the new values back to userspace. */
		if (!ret) {
			idx = i;
			do {
				ret = new_to_user(cs->controls + idx,
						helpers[idx].ctrl);
				idx = helpers[idx].next;
			} while (!ret && idx);
		}
		v4l2_ctrl_unlock(master);
	}

	if (cs->count > ARRAY_SIZE(helper))
		kvfree(helpers);
	return ret;
}