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
struct m5mols_info {int /*<<< orphan*/  lock; scalar_t__ ctrl_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MONITOR ; 
 int /*<<< orphan*/  REG_SAMSUNG_TECHWIN ; 
 scalar_t__ is_manufacturer (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int m5mols_auto_focus_stop (struct m5mols_info*) ; 
 int m5mols_fw_start (struct v4l2_subdev*) ; 
 int m5mols_sensor_power (struct m5mols_info*,int) ; 
 int m5mols_set_mode (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_warn (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int m5mols_s_power(struct v4l2_subdev *sd, int on)
{
	struct m5mols_info *info = to_m5mols(sd);
	int ret;

	mutex_lock(&info->lock);

	if (on) {
		ret = m5mols_sensor_power(info, true);
		if (!ret)
			ret = m5mols_fw_start(sd);
	} else {
		if (is_manufacturer(info, REG_SAMSUNG_TECHWIN)) {
			ret = m5mols_set_mode(info, REG_MONITOR);
			if (!ret)
				ret = m5mols_auto_focus_stop(info);
			if (ret < 0)
				v4l2_warn(sd, "Soft landing lens failed\n");
		}
		ret = m5mols_sensor_power(info, false);

		info->ctrl_sync = 0;
	}

	mutex_unlock(&info->lock);
	return ret;
}