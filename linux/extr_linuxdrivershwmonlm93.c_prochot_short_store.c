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
struct lm93_data {int config; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM93_REG_CONFIG ; 
 struct lm93_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  lm93_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t prochot_short_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct lm93_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	if (val)
		data->config |= 0x10;
	else
		data->config &= ~0x10;
	lm93_write_byte(client, LM93_REG_CONFIG, data->config);
	mutex_unlock(&data->update_lock);
	return count;
}