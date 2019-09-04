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
struct i2c_client {int dummy; } ;
struct emc2103_data {int fan_rpm_control; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  REG_FAN_CONF1 ; 
 struct emc2103_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_u8_from_i2c (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t pwm1_enable_store(struct device *dev,
				 struct device_attribute *da, const char *buf,
				 size_t count)
{
	struct emc2103_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long new_value;
	u8 conf_reg;

	int result = kstrtol(buf, 10, &new_value);
	if (result < 0)
		return result;

	mutex_lock(&data->update_lock);
	switch (new_value) {
	case 0:
		data->fan_rpm_control = false;
		break;
	case 3:
		data->fan_rpm_control = true;
		break;
	default:
		count = -EINVAL;
		goto err;
	}

	result = read_u8_from_i2c(client, REG_FAN_CONF1, &conf_reg);
	if (result) {
		count = result;
		goto err;
	}

	if (data->fan_rpm_control)
		conf_reg |= 0x80;
	else
		conf_reg &= ~0x80;

	i2c_smbus_write_byte_data(client, REG_FAN_CONF1, conf_reg);
err:
	mutex_unlock(&data->update_lock);
	return count;
}