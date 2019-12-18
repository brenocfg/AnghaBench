#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct elan_tp_data {int baseline_ready; int /*<<< orphan*/  sysfs_mutex; int /*<<< orphan*/  mode; int /*<<< orphan*/  client; TYPE_1__* ops; int /*<<< orphan*/  min_baseline; int /*<<< orphan*/  max_baseline; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* set_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* get_baseline_data ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_ENABLE_CALIBRATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct elan_tp_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t acquire_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct elan_tp_data *data = i2c_get_clientdata(client);
	int error;
	int retval;

	retval = mutex_lock_interruptible(&data->sysfs_mutex);
	if (retval)
		return retval;

	disable_irq(client->irq);

	data->baseline_ready = false;

	data->mode |= ETP_ENABLE_CALIBRATE;
	retval = data->ops->set_mode(data->client, data->mode);
	if (retval) {
		dev_err(dev, "Failed to enable calibration mode to get baseline: %d\n",
			retval);
		goto out;
	}

	msleep(250);

	retval = data->ops->get_baseline_data(data->client, true,
					      &data->max_baseline);
	if (retval) {
		dev_err(dev, "Failed to read max baseline form device: %d\n",
			retval);
		goto out_disable_calibrate;
	}

	retval = data->ops->get_baseline_data(data->client, false,
					      &data->min_baseline);
	if (retval) {
		dev_err(dev, "Failed to read min baseline form device: %d\n",
			retval);
		goto out_disable_calibrate;
	}

	data->baseline_ready = true;

out_disable_calibrate:
	data->mode &= ~ETP_ENABLE_CALIBRATE;
	error = data->ops->set_mode(data->client, data->mode);
	if (error) {
		dev_err(dev, "Failed to disable calibration mode after acquiring baseline: %d\n",
			error);
		if (!retval)
			retval = error;
	}
out:
	enable_irq(client->irq);
	mutex_unlock(&data->sysfs_mutex);
	return retval ?: count;
}