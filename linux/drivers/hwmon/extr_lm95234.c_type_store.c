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
typedef  int /*<<< orphan*/  u8 ;
struct lm95234_data {int valid; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  sensor_type; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LM95234_REG_REM_MODEL ; 
 struct lm95234_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int lm95234_update_device (struct lm95234_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t type_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct lm95234_data *data = dev_get_drvdata(dev);
	unsigned long val;
	u8 mask = to_sensor_dev_attr(attr)->index;
	int ret = lm95234_update_device(data);

	if (ret)
		return ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret < 0)
		return ret;

	if (val != 1 && val != 2)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	if (val == 1)
		data->sensor_type |= mask;
	else
		data->sensor_type &= ~mask;
	data->valid = false;
	i2c_smbus_write_byte_data(data->client, LM95234_REG_REM_MODEL,
				  data->sensor_type);
	mutex_unlock(&data->update_lock);

	return count;
}