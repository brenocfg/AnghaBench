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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7x10_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ADT7X10_REG_TEMP ; 
 int /*<<< orphan*/  ADT7X10_TEMP_TO_REG (long) ; 
 int adt7x10_write_word (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adt7x10_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t adt7x10_temp_store(struct device *dev,
				  struct device_attribute *da,
				  const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct adt7x10_data *data = dev_get_drvdata(dev);
	int nr = attr->index;
	long temp;
	int ret;

	ret = kstrtol(buf, 10, &temp);
	if (ret)
		return ret;

	mutex_lock(&data->update_lock);
	data->temp[nr] = ADT7X10_TEMP_TO_REG(temp);
	ret = adt7x10_write_word(dev, ADT7X10_REG_TEMP[nr], data->temp[nr]);
	if (ret)
		count = ret;
	mutex_unlock(&data->update_lock);
	return count;
}