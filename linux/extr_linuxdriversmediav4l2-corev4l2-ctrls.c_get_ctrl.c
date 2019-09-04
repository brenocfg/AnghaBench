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
struct v4l2_ext_control {int dummy; } ;
struct v4l2_ctrl {scalar_t__ type; int flags; int ncontrols; struct v4l2_ctrl** cluster; int /*<<< orphan*/  is_int; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int V4L2_CTRL_FLAG_VOLATILE ; 
 int V4L2_CTRL_FLAG_WRITE_ONLY ; 
 scalar_t__ V4L2_CTRL_TYPE_INTEGER64 ; 
 int call_op (struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cur_to_new (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  cur_to_user (struct v4l2_ext_control*,struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  g_volatile_ctrl ; 
 int /*<<< orphan*/  new_to_user (struct v4l2_ext_control*,struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (struct v4l2_ctrl*) ; 

__attribute__((used)) static int get_ctrl(struct v4l2_ctrl *ctrl, struct v4l2_ext_control *c)
{
	struct v4l2_ctrl *master = ctrl->cluster[0];
	int ret = 0;
	int i;

	/* Compound controls are not supported. The new_to_user() and
	 * cur_to_user() calls below would need to be modified not to access
	 * userspace memory when called from get_ctrl().
	 */
	if (!ctrl->is_int && ctrl->type != V4L2_CTRL_TYPE_INTEGER64)
		return -EINVAL;

	if (ctrl->flags & V4L2_CTRL_FLAG_WRITE_ONLY)
		return -EACCES;

	v4l2_ctrl_lock(master);
	/* g_volatile_ctrl will update the current control values */
	if (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE) {
		for (i = 0; i < master->ncontrols; i++)
			cur_to_new(master->cluster[i]);
		ret = call_op(master, g_volatile_ctrl);
		new_to_user(c, ctrl);
	} else {
		cur_to_user(c, ctrl);
	}
	v4l2_ctrl_unlock(master);
	return ret;
}