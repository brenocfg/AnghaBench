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
struct noon010_info {int /*<<< orphan*/  hdl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int noon010_base_config (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  noon010_power_ctrl (struct v4l2_subdev*,int,int) ; 
 int power_disable (struct noon010_info*) ; 
 int power_enable (struct noon010_info*) ; 
 struct noon010_info* to_noon010 (struct v4l2_subdev*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int noon010_s_power(struct v4l2_subdev *sd, int on)
{
	struct noon010_info *info = to_noon010(sd);
	int ret;

	mutex_lock(&info->lock);
	if (on) {
		ret = power_enable(info);
		if (!ret)
			ret = noon010_base_config(sd);
	} else {
		noon010_power_ctrl(sd, false, true);
		ret = power_disable(info);
	}
	mutex_unlock(&info->lock);

	/* Restore the controls state */
	if (!ret && on)
		ret = v4l2_ctrl_handler_setup(&info->hdl);

	return ret;
}