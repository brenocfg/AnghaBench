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
struct v4l2_ctrl {int flags; scalar_t__ type; TYPE_1__* type_ops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* log ) (struct v4l2_ctrl const*) ;} ;

/* Variables and functions */
 int V4L2_CTRL_FLAG_DISABLED ; 
 int V4L2_CTRL_FLAG_GRABBED ; 
 int V4L2_CTRL_FLAG_INACTIVE ; 
 int V4L2_CTRL_FLAG_VOLATILE ; 
 int V4L2_CTRL_FLAG_WRITE_ONLY ; 
 scalar_t__ V4L2_CTRL_TYPE_CTRL_CLASS ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_ctrl const*) ; 

__attribute__((used)) static void log_ctrl(const struct v4l2_ctrl *ctrl,
		     const char *prefix, const char *colon)
{
	if (ctrl->flags & (V4L2_CTRL_FLAG_DISABLED | V4L2_CTRL_FLAG_WRITE_ONLY))
		return;
	if (ctrl->type == V4L2_CTRL_TYPE_CTRL_CLASS)
		return;

	pr_info("%s%s%s: ", prefix, colon, ctrl->name);

	ctrl->type_ops->log(ctrl);

	if (ctrl->flags & (V4L2_CTRL_FLAG_INACTIVE |
			   V4L2_CTRL_FLAG_GRABBED |
			   V4L2_CTRL_FLAG_VOLATILE)) {
		if (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
			pr_cont(" inactive");
		if (ctrl->flags & V4L2_CTRL_FLAG_GRABBED)
			pr_cont(" grabbed");
		if (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE)
			pr_cont(" volatile");
	}
	pr_cont("\n");
}