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
typedef  int /*<<< orphan*/  u16 ;
struct ina209_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  update_interval; int /*<<< orphan*/ * regs; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t INA209_CONFIGURATION ; 
 scalar_t__ IS_ERR (struct ina209_data*) ; 
 int PTR_ERR (struct ina209_data*) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ina209_interval_from_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ina209_reg_from_interval (int /*<<< orphan*/ ,long) ; 
 struct ina209_data* ina209_update_device (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ina209_interval_store(struct device *dev,
				     struct device_attribute *da,
				     const char *buf, size_t count)
{
	struct ina209_data *data = ina209_update_device(dev);
	long val;
	u16 regval;
	int ret;

	if (IS_ERR(data))
		return PTR_ERR(data);

	ret = kstrtol(buf, 10, &val);
	if (ret < 0)
		return ret;

	mutex_lock(&data->update_lock);
	regval = ina209_reg_from_interval(data->regs[INA209_CONFIGURATION],
					  val);
	i2c_smbus_write_word_swapped(data->client, INA209_CONFIGURATION,
				     regval);
	data->regs[INA209_CONFIGURATION] = regval;
	data->update_interval = ina209_interval_from_reg(regval);
	mutex_unlock(&data->update_lock);
	return count;
}