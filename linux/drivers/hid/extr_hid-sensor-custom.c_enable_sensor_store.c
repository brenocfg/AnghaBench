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
struct hid_sensor_custom {int enable; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hsdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct hid_sensor_custom* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sensor_hub_device_close (int /*<<< orphan*/ ) ; 
 int sensor_hub_device_open (int /*<<< orphan*/ ) ; 
 int set_power_report_state (struct hid_sensor_custom*,int) ; 

__attribute__((used)) static ssize_t enable_sensor_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct hid_sensor_custom *sensor_inst = dev_get_drvdata(dev);
	int value;
	int ret = -EINVAL;

	if (kstrtoint(buf, 0, &value) != 0)
		return -EINVAL;

	mutex_lock(&sensor_inst->mutex);
	if (value && !sensor_inst->enable) {
		ret = sensor_hub_device_open(sensor_inst->hsdev);
		if (ret)
			goto unlock_state;

		ret = set_power_report_state(sensor_inst, true);
		if (ret) {
			sensor_hub_device_close(sensor_inst->hsdev);
			goto unlock_state;
		}
		sensor_inst->enable = true;
	} else if (!value && sensor_inst->enable) {
		ret = set_power_report_state(sensor_inst, false);
		sensor_hub_device_close(sensor_inst->hsdev);
		sensor_inst->enable = false;
	}
unlock_state:
	mutex_unlock(&sensor_inst->mutex);
	if (ret < 0)
		return ret;

	return count;
}