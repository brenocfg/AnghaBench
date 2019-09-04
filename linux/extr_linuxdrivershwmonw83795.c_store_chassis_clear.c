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
struct w83795_data {int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  W83795_REG_ALARM (int) ; 
 int /*<<< orphan*/  W83795_REG_CLR_CHASSIS ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 unsigned long w83795_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83795_write (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t
store_chassis_clear(struct device *dev,
		    struct device_attribute *attr, const char *buf,
		    size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83795_data *data = i2c_get_clientdata(client);
	unsigned long val;

	if (kstrtoul(buf, 10, &val) < 0 || val != 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	val = w83795_read(client, W83795_REG_CLR_CHASSIS);
	val |= 0x80;
	w83795_write(client, W83795_REG_CLR_CHASSIS, val);

	/* Clear status and force cache refresh */
	w83795_read(client, W83795_REG_ALARM(5));
	data->valid = 0;
	mutex_unlock(&data->update_lock);
	return count;
}