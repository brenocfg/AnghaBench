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
struct lm95234_data {long* toffset; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (long,int) ; 
 int /*<<< orphan*/  LM95234_REG_OFFSET (int) ; 
 long clamp_val (int /*<<< orphan*/ ,int,int) ; 
 struct lm95234_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int kstrtol (char const*,int,long*) ; 
 int lm95234_update_device (struct lm95234_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t offset_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct lm95234_data *data = dev_get_drvdata(dev);
	int index = to_sensor_dev_attr(attr)->index;
	int ret = lm95234_update_device(data);
	long val;

	if (ret)
		return ret;

	ret = kstrtol(buf, 10, &val);
	if (ret < 0)
		return ret;

	/* Accuracy is 1/2 degrees C */
	val = clamp_val(DIV_ROUND_CLOSEST(val, 500), -128, 127);

	mutex_lock(&data->update_lock);
	data->toffset[index] = val;
	i2c_smbus_write_byte_data(data->client, LM95234_REG_OFFSET(index), val);
	mutex_unlock(&data->update_lock);

	return count;
}