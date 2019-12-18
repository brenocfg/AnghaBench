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
struct lm73_data {int ctrl; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 int LM73_CTRL_RES_SHIFT ; 
 int LM73_CTRL_TO_MASK ; 
 int /*<<< orphan*/  LM73_REG_CTRL ; 
 struct lm73_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 unsigned long* lm73_convrates ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t convrate_store(struct device *dev, struct device_attribute *da,
			      const char *buf, size_t count)
{
	struct lm73_data *data = dev_get_drvdata(dev);
	unsigned long convrate;
	s32 err;
	int res = 0;

	err = kstrtoul(buf, 10, &convrate);
	if (err < 0)
		return err;

	/*
	 * Convert the desired conversion rate into register bits.
	 * res is already initialized, and everything past the second-to-last
	 * value in the array is treated as belonging to the last value
	 * in the array.
	 */
	while (res < (ARRAY_SIZE(lm73_convrates) - 1) &&
			convrate > lm73_convrates[res])
		res++;

	mutex_lock(&data->lock);
	data->ctrl &= LM73_CTRL_TO_MASK;
	data->ctrl |= res << LM73_CTRL_RES_SHIFT;
	err = i2c_smbus_write_byte_data(data->client, LM73_REG_CTRL,
					data->ctrl);
	mutex_unlock(&data->lock);

	if (err < 0)
		return err;

	return count;
}