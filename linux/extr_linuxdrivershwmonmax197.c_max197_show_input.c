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
struct sensor_device_attribute {int index; } ;
struct max197_data {int /*<<< orphan*/  lock; scalar_t__ scale; int /*<<< orphan*/ * ctrl_bytes; TYPE_1__* pdata; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int s32 ;
struct TYPE_2__ {int (* convert ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int MAX197_SCALE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct max197_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ max197_is_full_range (struct max197_data*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t max197_show_input(struct device *dev,
				 struct device_attribute *devattr,
				 char *buf)
{
	struct max197_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int channel = attr->index;
	s32 value;
	int ret;

	if (mutex_lock_interruptible(&data->lock))
		return -ERESTARTSYS;

	ret = data->pdata->convert(data->ctrl_bytes[channel]);
	if (ret < 0) {
		dev_err(dev, "conversion failed\n");
		goto unlock;
	}
	value = ret;

	/*
	 * Coefficient to apply on raw value.
	 * See Table 1. Full Scale and Zero Scale in the MAX197 datasheet.
	 */
	if (data->scale) {
		value *= MAX197_SCALE;
		if (max197_is_full_range(data, channel))
			value *= 2;
		value /= 10000;
	}

	ret = sprintf(buf, "%d\n", value);

unlock:
	mutex_unlock(&data->lock);
	return ret;
}