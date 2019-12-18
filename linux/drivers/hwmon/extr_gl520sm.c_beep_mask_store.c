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
struct gl520_data {unsigned long alarm_mask; unsigned long beep_mask; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL520_REG_BEEP_MASK ; 
 struct gl520_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gl520_write_value (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t beep_mask_store(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t count)
{
	struct gl520_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long r;
	int err;

	err = kstrtoul(buf, 10, &r);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	r &= data->alarm_mask;
	data->beep_mask = r;
	gl520_write_value(client, GL520_REG_BEEP_MASK, r);
	mutex_unlock(&data->update_lock);
	return count;
}