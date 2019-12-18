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
struct sensor_device_attribute {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct abx500_temp {unsigned long* max_hyst; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MAX_TEMP ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct abx500_temp* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  threshold_updated (struct abx500_temp*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t max_hyst_store(struct device *dev,
			      struct device_attribute *devattr,
			      const char *buf, size_t count)
{
	unsigned long val;
	struct abx500_temp *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int res = kstrtoul(buf, 10, &val);
	if (res < 0)
		return res;

	val = clamp_val(val, 0, DEFAULT_MAX_TEMP);

	mutex_lock(&data->lock);
	data->max_hyst[attr->index] = val;
	threshold_updated(data);
	mutex_unlock(&data->lock);

	return count;
}