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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int /*<<< orphan*/  name; } ;
struct ov965x {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __g_volatile_ctrl (struct ov965x*,struct v4l2_ctrl*) ; 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ov965x* to_ov965x (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov965x_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct ov965x *ov965x = to_ov965x(sd);
	int ret;

	v4l2_dbg(1, debug, sd, "g_ctrl: %s\n", ctrl->name);

	mutex_lock(&ov965x->lock);
	ret = __g_volatile_ctrl(ov965x, ctrl);
	mutex_unlock(&ov965x->lock);
	return ret;
}