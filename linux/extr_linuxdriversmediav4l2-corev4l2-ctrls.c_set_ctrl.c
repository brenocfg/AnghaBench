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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_fh {int dummy; } ;
struct v4l2_ctrl {int ncontrols; int is_new; scalar_t__ val; scalar_t__ manual_mode_value; scalar_t__ has_volatiles; scalar_t__ is_auto; int /*<<< orphan*/  p_new; struct v4l2_ctrl** cluster; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_cur_manual (struct v4l2_ctrl*) ; 
 int try_or_set_cluster (struct v4l2_fh*,struct v4l2_ctrl*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_from_auto_cluster (struct v4l2_ctrl*) ; 
 int validate_new (struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_ctrl(struct v4l2_fh *fh, struct v4l2_ctrl *ctrl, u32 ch_flags)
{
	struct v4l2_ctrl *master = ctrl->cluster[0];
	int ret;
	int i;

	/* Reset the 'is_new' flags of the cluster */
	for (i = 0; i < master->ncontrols; i++)
		if (master->cluster[i])
			master->cluster[i]->is_new = 0;

	ret = validate_new(ctrl, ctrl->p_new);
	if (ret)
		return ret;

	/* For autoclusters with volatiles that are switched from auto to
	   manual mode we have to update the current volatile values since
	   those will become the initial manual values after such a switch. */
	if (master->is_auto && master->has_volatiles && ctrl == master &&
	    !is_cur_manual(master) && ctrl->val == master->manual_mode_value)
		update_from_auto_cluster(master);

	ctrl->is_new = 1;
	return try_or_set_cluster(fh, master, true, ch_flags);
}