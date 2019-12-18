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
struct sensor_device_attribute {int index; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm9240_data {int* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM9240_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  FAN_FROM_REG (unsigned int,int) ; 
 int /*<<< orphan*/  adm9240_write_fan_div (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct adm9240_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adm9240_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int nr = attr->index;
	u8 new_div;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	if (!val) {
		data->fan_min[nr] = 255;
		new_div = data->fan_div[nr];

		dev_dbg(&client->dev, "fan%u low limit set disabled\n",
				nr + 1);

	} else if (val < 1350000 / (8 * 254)) {
		new_div = 3;
		data->fan_min[nr] = 254;

		dev_dbg(&client->dev, "fan%u low limit set minimum %u\n",
				nr + 1, FAN_FROM_REG(254, 1 << new_div));

	} else {
		unsigned int new_min = 1350000 / val;

		new_div = 0;
		while (new_min > 192 && new_div < 3) {
			new_div++;
			new_min /= 2;
		}
		if (!new_min) /* keep > 0 */
			new_min++;

		data->fan_min[nr] = new_min;

		dev_dbg(&client->dev, "fan%u low limit set fan speed %u\n",
				nr + 1, FAN_FROM_REG(new_min, 1 << new_div));
	}

	if (new_div != data->fan_div[nr]) {
		data->fan_div[nr] = new_div;
		adm9240_write_fan_div(client, nr, new_div);
	}
	i2c_smbus_write_byte_data(client, ADM9240_REG_FAN_MIN(nr),
			data->fan_min[nr]);

	mutex_unlock(&data->update_lock);
	return count;
}