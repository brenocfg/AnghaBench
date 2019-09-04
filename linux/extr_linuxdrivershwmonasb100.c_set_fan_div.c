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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct asb100_data {int* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASB100_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  ASB100_REG_PIN ; 
 int /*<<< orphan*/  ASB100_REG_VID_FANDIV ; 
 int /*<<< orphan*/  DIV_FROM_REG (int) ; 
 int DIV_TO_REG (unsigned long) ; 
 unsigned long FAN_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int FAN_TO_REG (unsigned long,int /*<<< orphan*/ ) ; 
 int asb100_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asb100_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct asb100_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_div(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct asb100_data *data = i2c_get_clientdata(client);
	unsigned long min;
	int reg;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	min = FAN_FROM_REG(data->fan_min[nr],
			DIV_FROM_REG(data->fan_div[nr]));
	data->fan_div[nr] = DIV_TO_REG(val);

	switch (nr) {
	case 0:	/* fan 1 */
		reg = asb100_read_value(client, ASB100_REG_VID_FANDIV);
		reg = (reg & 0xcf) | (data->fan_div[0] << 4);
		asb100_write_value(client, ASB100_REG_VID_FANDIV, reg);
		break;

	case 1:	/* fan 2 */
		reg = asb100_read_value(client, ASB100_REG_VID_FANDIV);
		reg = (reg & 0x3f) | (data->fan_div[1] << 6);
		asb100_write_value(client, ASB100_REG_VID_FANDIV, reg);
		break;

	case 2:	/* fan 3 */
		reg = asb100_read_value(client, ASB100_REG_PIN);
		reg = (reg & 0x3f) | (data->fan_div[2] << 6);
		asb100_write_value(client, ASB100_REG_PIN, reg);
		break;
	}

	data->fan_min[nr] =
		FAN_TO_REG(min, DIV_FROM_REG(data->fan_div[nr]));
	asb100_write_value(client, ASB100_REG_FAN_MIN(nr), data->fan_min[nr]);

	mutex_unlock(&data->update_lock);

	return count;
}