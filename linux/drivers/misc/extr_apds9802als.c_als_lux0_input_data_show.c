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
struct als_data {int /*<<< orphan*/  mutex; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int als_wait_for_data_ready (struct device*) ; 
 struct als_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t als_lux0_input_data_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct als_data *data = i2c_get_clientdata(client);
	int ret_val;
	int temp;

	/* Protect against parallel reads */
	pm_runtime_get_sync(dev);
	mutex_lock(&data->mutex);

	/* clear EOC interrupt status */
	i2c_smbus_write_byte(client, 0x40);
	/* start measurement */
	temp = i2c_smbus_read_byte_data(client, 0x81);
	i2c_smbus_write_byte_data(client, 0x81, temp | 0x08);

	ret_val = als_wait_for_data_ready(dev);
	if (ret_val < 0)
		goto failed;

	temp = i2c_smbus_read_byte_data(client, 0x8C); /* LSB data */
	if (temp < 0) {
		ret_val = temp;
		goto failed;
	}
	ret_val = i2c_smbus_read_byte_data(client, 0x8D); /* MSB data */
	if (ret_val < 0)
		goto failed;

	mutex_unlock(&data->mutex);
	pm_runtime_put_sync(dev);

	temp = (ret_val << 8) | temp;
	return sprintf(buf, "%d\n", temp);
failed:
	mutex_unlock(&data->mutex);
	pm_runtime_put_sync(dev);
	return ret_val;
}