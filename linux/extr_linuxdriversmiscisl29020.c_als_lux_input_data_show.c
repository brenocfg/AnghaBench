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
typedef  int ssize_t ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int sprintf (char*,char*,unsigned long) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t als_lux_input_data_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	int ret_val, val;
	unsigned long int lux;
	int temp;

	pm_runtime_get_sync(dev);
	msleep(100);

	mutex_lock(&mutex);
	temp = i2c_smbus_read_byte_data(client, 0x02); /* MSB data */
	if (temp < 0) {
		pm_runtime_put_sync(dev);
		mutex_unlock(&mutex);
		return temp;
	}

	ret_val = i2c_smbus_read_byte_data(client, 0x01); /* LSB data */
	mutex_unlock(&mutex);

	if (ret_val < 0) {
		pm_runtime_put_sync(dev);
		return ret_val;
	}

	ret_val |= temp << 8;
	val = i2c_smbus_read_byte_data(client, 0x00);
	pm_runtime_put_sync(dev);
	if (val < 0)
		return val;
	lux = ((((1 << (2 * (val & 3))))*1000) * ret_val) / 65536;
	return sprintf(buf, "%ld\n", lux);
}