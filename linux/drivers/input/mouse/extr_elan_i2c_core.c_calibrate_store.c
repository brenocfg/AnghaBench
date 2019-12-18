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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct elan_tp_data {int /*<<< orphan*/  sysfs_mutex; int /*<<< orphan*/  mode; struct i2c_client* client; TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* set_mode ) (struct i2c_client*,int /*<<< orphan*/ ) ;int (* calibrate ) (struct i2c_client*) ;int (* calibrate_result ) (struct i2c_client*,int*) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int ETP_CALIBRATE_MAX_LEN ; 
 int /*<<< orphan*/  ETP_ENABLE_CALIBRATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct elan_tp_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int stub2 (struct i2c_client*) ; 
 int stub3 (struct i2c_client*,int*) ; 
 int stub4 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t calibrate_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct elan_tp_data *data = i2c_get_clientdata(client);
	int tries = 20;
	int retval;
	int error;
	u8 val[ETP_CALIBRATE_MAX_LEN];

	retval = mutex_lock_interruptible(&data->sysfs_mutex);
	if (retval)
		return retval;

	disable_irq(client->irq);

	data->mode |= ETP_ENABLE_CALIBRATE;
	retval = data->ops->set_mode(client, data->mode);
	if (retval) {
		dev_err(dev, "failed to enable calibration mode: %d\n",
			retval);
		goto out;
	}

	retval = data->ops->calibrate(client);
	if (retval) {
		dev_err(dev, "failed to start calibration: %d\n",
			retval);
		goto out_disable_calibrate;
	}

	val[0] = 0xff;
	do {
		/* Wait 250ms before checking if calibration has completed. */
		msleep(250);

		retval = data->ops->calibrate_result(client, val);
		if (retval)
			dev_err(dev, "failed to check calibration result: %d\n",
				retval);
		else if (val[0] == 0)
			break; /* calibration done */

	} while (--tries);

	if (tries == 0) {
		dev_err(dev, "failed to calibrate. Timeout.\n");
		retval = -ETIMEDOUT;
	}

out_disable_calibrate:
	data->mode &= ~ETP_ENABLE_CALIBRATE;
	error = data->ops->set_mode(data->client, data->mode);
	if (error) {
		dev_err(dev, "failed to disable calibration mode: %d\n",
			error);
		if (!retval)
			retval = error;
	}
out:
	enable_irq(client->irq);
	mutex_unlock(&data->sysfs_mutex);
	return retval ?: count;
}