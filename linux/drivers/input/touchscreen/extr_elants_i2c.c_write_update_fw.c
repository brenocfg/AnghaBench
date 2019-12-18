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
struct elants_data {int /*<<< orphan*/  sysfs_mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int elants_i2c_fw_update (struct elants_data*) ; 
 struct elants_data* i2c_get_clientdata (struct i2c_client*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t write_update_fw(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct elants_data *ts = i2c_get_clientdata(client);
	int error;

	error = mutex_lock_interruptible(&ts->sysfs_mutex);
	if (error)
		return error;

	error = elants_i2c_fw_update(ts);
	dev_dbg(dev, "firmware update result: %d\n", error);

	mutex_unlock(&ts->sysfs_mutex);
	return error ?: count;
}