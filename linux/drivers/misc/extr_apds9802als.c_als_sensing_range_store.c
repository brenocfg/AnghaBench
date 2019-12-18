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
 int ERANGE ; 
 struct als_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t als_sensing_range_store(struct device *dev,
		struct device_attribute *attr, const  char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct als_data *data = i2c_get_clientdata(client);
	int ret_val;
	unsigned long val;

	ret_val = kstrtoul(buf, 10, &val);
	if (ret_val)
		return ret_val;

	if (val < 4096)
		val = 1;
	else if (val < 65536)
		val = 2;
	else
		return -ERANGE;

	pm_runtime_get_sync(dev);

	/* Make sure nobody else reads/modifies/writes 0x81 while we
	   are active */
	mutex_lock(&data->mutex);

	ret_val = i2c_smbus_read_byte_data(client, 0x81);
	if (ret_val < 0)
		goto fail;

	/* Reset the bits before setting them */
	ret_val = ret_val & 0xFA;

	if (val == 1) /* Setting detection range up to 4k LUX */
		ret_val = (ret_val | 0x01);
	else /* Setting detection range up to 64k LUX*/
		ret_val = (ret_val | 0x00);

	ret_val = i2c_smbus_write_byte_data(client, 0x81, ret_val);

	if (ret_val >= 0) {
		/* All OK */
		mutex_unlock(&data->mutex);
		pm_runtime_put_sync(dev);
		return count;
	}
fail:
	mutex_unlock(&data->mutex);
	pm_runtime_put_sync(dev);
	return ret_val;
}