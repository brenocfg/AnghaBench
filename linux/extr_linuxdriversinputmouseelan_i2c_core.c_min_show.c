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
struct elan_tp_data {int min_baseline; int /*<<< orphan*/  sysfs_mutex; int /*<<< orphan*/  baseline_ready; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct elan_tp_data* i2c_get_clientdata (struct i2c_client*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t min_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct elan_tp_data *data = i2c_get_clientdata(client);
	int retval;

	retval = mutex_lock_interruptible(&data->sysfs_mutex);
	if (retval)
		return retval;

	if (!data->baseline_ready) {
		retval = -ENODATA;
		goto out;
	}

	retval = snprintf(buf, PAGE_SIZE, "%d", data->min_baseline);

out:
	mutex_unlock(&data->sysfs_mutex);
	return retval;
}