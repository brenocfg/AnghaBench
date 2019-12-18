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
struct noon010_info {int streaming; int /*<<< orphan*/  lock; scalar_t__ apply_new_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int noon010_power_ctrl (struct v4l2_subdev*,int,int) ; 
 int noon010_set_params (struct v4l2_subdev*) ; 
 struct noon010_info* to_noon010 (struct v4l2_subdev*) ; 

__attribute__((used)) static int noon010_s_stream(struct v4l2_subdev *sd, int on)
{
	struct noon010_info *info = to_noon010(sd);
	int ret = 0;

	mutex_lock(&info->lock);
	if (!info->streaming != !on) {
		ret = noon010_power_ctrl(sd, false, !on);
		if (!ret)
			info->streaming = on;
	}
	if (!ret && on && info->apply_new_cfg) {
		ret = noon010_set_params(sd);
		if (!ret)
			info->apply_new_cfg = 0;
	}
	mutex_unlock(&info->lock);
	return ret;
}