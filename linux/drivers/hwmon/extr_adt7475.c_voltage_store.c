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
struct sensor_device_attribute_2 {size_t nr; size_t index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int** voltage; int /*<<< orphan*/  lock; int /*<<< orphan*/  bypass_attn; struct i2c_client* client; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ADT7475_VOLTAGE_COUNT ; 
 size_t EINVAL ; 
 size_t MIN ; 
 unsigned char REG_VTT_MAX ; 
 unsigned char REG_VTT_MIN ; 
 unsigned char VOLTAGE_MAX_REG (size_t) ; 
 unsigned char VOLTAGE_MIN_REG (size_t) ; 
 struct adt7475_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,unsigned char,int) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int volt2reg (size_t,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t voltage_store(struct device *dev,
			     struct device_attribute *attr, const char *buf,
			     size_t count)
{

	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct adt7475_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned char reg;
	long val;

	if (kstrtol(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->lock);

	data->voltage[sattr->nr][sattr->index] =
				volt2reg(sattr->index, val, data->bypass_attn);

	if (sattr->index < ADT7475_VOLTAGE_COUNT) {
		if (sattr->nr == MIN)
			reg = VOLTAGE_MIN_REG(sattr->index);
		else
			reg = VOLTAGE_MAX_REG(sattr->index);
	} else {
		if (sattr->nr == MIN)
			reg = REG_VTT_MIN;
		else
			reg = REG_VTT_MAX;
	}

	i2c_smbus_write_byte_data(client, reg,
				  data->voltage[sattr->nr][sattr->index] >> 2);
	mutex_unlock(&data->lock);

	return count;
}