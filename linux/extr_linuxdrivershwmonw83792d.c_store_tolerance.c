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
struct w83792d_data {int* tolerance; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute {int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * W83792D_REG_TOLERANCE ; 
 int clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct w83792d_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83792d_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83792d_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_tolerance(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index - 1;
	struct i2c_client *client = to_i2c_client(dev);
	struct w83792d_data *data = i2c_get_clientdata(client);
	u8 tol_tmp, tol_mask;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	tol_mask = w83792d_read_value(client,
		W83792D_REG_TOLERANCE[nr]) & ((nr == 1) ? 0x0f : 0xf0);
	tol_tmp = clamp_val(val, 0, 15);
	tol_tmp &= 0x0f;
	data->tolerance[nr] = tol_tmp;
	if (nr == 1)
		tol_tmp <<= 4;
	w83792d_write_value(client, W83792D_REG_TOLERANCE[nr],
		tol_mask | tol_tmp);
	mutex_unlock(&data->update_lock);

	return count;
}