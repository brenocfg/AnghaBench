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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  config4; struct i2c_client* client; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG4_MAXDUTY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  REG_CONFIG4 ; 
 struct adt7475_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t pwm_use_point2_pwm_at_crit_store(struct device *dev,
					struct device_attribute *devattr,
					const char *buf, size_t count)
{
	struct adt7475_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;

	if (kstrtol(buf, 10, &val))
		return -EINVAL;
	if (val != 0 && val != 1)
		return -EINVAL;

	mutex_lock(&data->lock);
	data->config4 = i2c_smbus_read_byte_data(client, REG_CONFIG4);
	if (val)
		data->config4 |= CONFIG4_MAXDUTY;
	else
		data->config4 &= ~CONFIG4_MAXDUTY;
	i2c_smbus_write_byte_data(client, REG_CONFIG4, data->config4);
	mutex_unlock(&data->lock);

	return count;
}