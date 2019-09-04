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
struct lm95234_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; int /*<<< orphan*/  interval; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM95234_REG_CONVRATE ; 
 struct lm95234_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int lm95234_update_device (struct lm95234_data*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long* update_intervals ; 

__attribute__((used)) static ssize_t update_interval_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct lm95234_data *data = dev_get_drvdata(dev);
	int ret = lm95234_update_device(data);
	unsigned long val;
	u8 regval;

	if (ret)
		return ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret < 0)
		return ret;

	for (regval = 0; regval < 3; regval++) {
		if (val <= update_intervals[regval])
			break;
	}

	mutex_lock(&data->update_lock);
	data->interval = msecs_to_jiffies(update_intervals[regval]);
	i2c_smbus_write_byte_data(data->client, LM95234_REG_CONVRATE, regval);
	mutex_unlock(&data->update_lock);

	return count;
}