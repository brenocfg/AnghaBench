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
struct TYPE_2__ {int /*<<< orphan*/  min_interval; } ;
struct kxtj9_data {int /*<<< orphan*/  last_poll_interval; TYPE_1__ pdata; struct input_dev* input_dev; } ;
struct input_dev {int /*<<< orphan*/  mutex; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct kxtj9_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  kxtj9_update_odr (struct kxtj9_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t kxtj9_set_poll(struct device *dev, struct device_attribute *attr,
						const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct kxtj9_data *tj9 = i2c_get_clientdata(client);
	struct input_dev *input_dev = tj9->input_dev;
	unsigned int interval;
	int error;

	error = kstrtouint(buf, 10, &interval);
	if (error < 0)
		return error;

	/* Lock the device to prevent races with open/close (and itself) */
	mutex_lock(&input_dev->mutex);

	disable_irq(client->irq);

	/*
	 * Set current interval to the greater of the minimum interval or
	 * the requested interval
	 */
	tj9->last_poll_interval = max(interval, tj9->pdata.min_interval);

	kxtj9_update_odr(tj9, tj9->last_poll_interval);

	enable_irq(client->irq);
	mutex_unlock(&input_dev->mutex);

	return count;
}