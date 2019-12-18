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
typedef  int /*<<< orphan*/  u8 ;
struct sensor_device_attribute {int index; } ;
struct lm63_data {int* temp8; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  temp2_offset; int /*<<< orphan*/  remote_unsigned; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM63_REG_LOCAL_HIGH ; 
 int /*<<< orphan*/  LM63_REG_LUT_TEMP (int) ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_TCRIT ; 
 int TEMP8U_TO_REG (int /*<<< orphan*/ ) ; 
 int TEMP8_TO_REG (long) ; 
 struct lm63_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int lut_temp_to_reg (struct lm63_data*,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp8(struct device *dev, struct device_attribute *devattr,
			 const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct lm63_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int nr = attr->index;
	long val;
	int err;
	int temp;
	u8 reg;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	switch (nr) {
	case 2:
		reg = LM63_REG_REMOTE_TCRIT;
		if (data->remote_unsigned)
			temp = TEMP8U_TO_REG(val - data->temp2_offset);
		else
			temp = TEMP8_TO_REG(val - data->temp2_offset);
		break;
	case 1:
		reg = LM63_REG_LOCAL_HIGH;
		temp = TEMP8_TO_REG(val);
		break;
	default:	/* lookup table */
		reg = LM63_REG_LUT_TEMP(nr - 3);
		temp = lut_temp_to_reg(data, val);
	}
	data->temp8[nr] = temp;
	i2c_smbus_write_byte_data(client, reg, temp);
	mutex_unlock(&data->update_lock);
	return count;
}