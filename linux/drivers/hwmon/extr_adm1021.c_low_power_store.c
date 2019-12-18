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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1021_data {char low_power; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1021_REG_CONFIG_R ; 
 int /*<<< orphan*/  ADM1021_REG_CONFIG_W ; 
 struct adm1021_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t low_power_store(struct device *dev,
			       struct device_attribute *devattr,
			       const char *buf, size_t count)
{
	struct adm1021_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	char low_power;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;
	low_power = val != 0;

	mutex_lock(&data->update_lock);
	if (low_power != data->low_power) {
		int config = i2c_smbus_read_byte_data(
			client, ADM1021_REG_CONFIG_R);
		data->low_power = low_power;
		i2c_smbus_write_byte_data(client, ADM1021_REG_CONFIG_W,
			(config & 0xBF) | (low_power << 6));
	}
	mutex_unlock(&data->update_lock);

	return count;
}