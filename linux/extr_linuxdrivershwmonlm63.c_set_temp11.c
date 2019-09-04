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
struct lm63_data {int* temp11; int /*<<< orphan*/  update_lock; scalar_t__ temp2_offset; scalar_t__ remote_unsigned; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  LM63_REG_REMOTE_HIGH_LSB 133 
#define  LM63_REG_REMOTE_HIGH_MSB 132 
#define  LM63_REG_REMOTE_LOW_LSB 131 
#define  LM63_REG_REMOTE_LOW_MSB 130 
#define  LM63_REG_REMOTE_OFFSET_LSB 129 
#define  LM63_REG_REMOTE_OFFSET_MSB 128 
 int TEMP11U_TO_REG (scalar_t__) ; 
 int TEMP11_TO_REG (scalar_t__) ; 
 struct lm63_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/  const,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp11(struct device *dev, struct device_attribute *devattr,
			  const char *buf, size_t count)
{
	static const u8 reg[6] = {
		LM63_REG_REMOTE_LOW_MSB,
		LM63_REG_REMOTE_LOW_LSB,
		LM63_REG_REMOTE_HIGH_MSB,
		LM63_REG_REMOTE_HIGH_LSB,
		LM63_REG_REMOTE_OFFSET_MSB,
		LM63_REG_REMOTE_OFFSET_LSB,
	};

	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct lm63_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int err;
	int nr = attr->index;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	if (data->remote_unsigned && nr == 2)
		data->temp11[nr] = TEMP11U_TO_REG(val - data->temp2_offset);
	else
		data->temp11[nr] = TEMP11_TO_REG(val - data->temp2_offset);

	i2c_smbus_write_byte_data(client, reg[(nr - 1) * 2],
				  data->temp11[nr] >> 8);
	i2c_smbus_write_byte_data(client, reg[(nr - 1) * 2 + 1],
				  data->temp11[nr] & 0xff);
	mutex_unlock(&data->update_lock);
	return count;
}