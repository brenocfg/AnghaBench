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
struct smsc47m1_data {int* fan_preload; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * fan_div; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 long DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * SMSC47M1_REG_FAN_PRELOAD ; 
 struct smsc47m1_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsc47m1_write_value (struct smsc47m1_data*,int /*<<< orphan*/ ,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct smsc47m1_data *data = dev_get_drvdata(dev);
	int nr = attr->index;
	long rpmdiv;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	rpmdiv = val * DIV_FROM_REG(data->fan_div[nr]);

	if (983040 > 192 * rpmdiv || 2 * rpmdiv > 983040) {
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}

	data->fan_preload[nr] = 192 - ((983040 + rpmdiv / 2) / rpmdiv);
	smsc47m1_write_value(data, SMSC47M1_REG_FAN_PRELOAD[nr],
			     data->fan_preload[nr]);
	mutex_unlock(&data->update_lock);

	return count;
}