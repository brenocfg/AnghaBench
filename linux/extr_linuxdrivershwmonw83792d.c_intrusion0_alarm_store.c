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
struct w83792d_data {int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  W83792D_REG_CHASSIS_CLR ; 
 struct w83792d_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int w83792d_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83792d_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
intrusion0_alarm_store(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83792d_data *data = i2c_get_clientdata(client);
	unsigned long val;
	u8 reg;

	if (kstrtoul(buf, 10, &val) || val != 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	reg = w83792d_read_value(client, W83792D_REG_CHASSIS_CLR);
	w83792d_write_value(client, W83792D_REG_CHASSIS_CLR, reg | 0x80);
	data->valid = 0;		/* Force cache refresh */
	mutex_unlock(&data->update_lock);

	return count;
}