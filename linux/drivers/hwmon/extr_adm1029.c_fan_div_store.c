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
typedef  int u8 ;
struct sensor_device_attribute {size_t index; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1029_data {int* fan_div; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ADM1029_REG_FAN_DIV ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 struct adm1029_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_div_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	struct adm1029_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	u8 reg;
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return ret;

	mutex_lock(&data->update_lock);

	/*Read actual config */
	reg = i2c_smbus_read_byte_data(client,
				       ADM1029_REG_FAN_DIV[attr->index]);

	switch (val) {
	case 1:
		val = 1;
		break;
	case 2:
		val = 2;
		break;
	case 4:
		val = 3;
		break;
	default:
		mutex_unlock(&data->update_lock);
		dev_err(&client->dev,
			"fan_div value %ld not supported. Choose one of 1, 2 or 4!\n",
			val);
		return -EINVAL;
	}
	/* Update the value */
	reg = (reg & 0x3F) | (val << 6);

	/* Update the cache */
	data->fan_div[attr->index] = reg;

	/* Write value */
	i2c_smbus_write_byte_data(client,
				  ADM1029_REG_FAN_DIV[attr->index], reg);
	mutex_unlock(&data->update_lock);

	return count;
}