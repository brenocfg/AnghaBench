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
struct sensor_device_attribute {int index; } ;
struct max6650_data {int alarm; int valid; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct max6650_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct max6650_data*) ; 
 struct max6650_data* max6650_update_device (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t alarm_show(struct device *dev,
			  struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct max6650_data *data = max6650_update_device(dev);
	bool alarm;

	if (IS_ERR(data))
		return PTR_ERR(data);

	alarm = data->alarm & attr->index;
	if (alarm) {
		mutex_lock(&data->update_lock);
		data->alarm &= ~attr->index;
		data->valid = false;
		mutex_unlock(&data->update_lock);
	}

	return sprintf(buf, "%d\n", alarm);
}