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
struct tmp401_data {int config; int temp_crit_hyst; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; int /*<<< orphan*/ ** temp; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ IS_ERR (struct tmp401_data*) ; 
 size_t PTR_ERR (struct tmp401_data*) ; 
 int TMP401_CONFIG_RANGE ; 
 int /*<<< orphan*/  TMP401_TEMP_CRIT_HYST ; 
 long clamp_val (long,int,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tmp401_register_to_temp (int /*<<< orphan*/ ,int) ; 
 struct tmp401_data* tmp401_update_device (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_crit_hyst_store(struct device *dev,
				    struct device_attribute *devattr,
				    const char *buf, size_t count)
{
	int temp, index = to_sensor_dev_attr(devattr)->index;
	struct tmp401_data *data = tmp401_update_device(dev);
	long val;
	u8 reg;

	if (IS_ERR(data))
		return PTR_ERR(data);

	if (kstrtol(buf, 10, &val))
		return -EINVAL;

	if (data->config & TMP401_CONFIG_RANGE)
		val = clamp_val(val, -64000, 191000);
	else
		val = clamp_val(val, 0, 127000);

	mutex_lock(&data->update_lock);
	temp = tmp401_register_to_temp(data->temp[3][index], data->config);
	val = clamp_val(val, temp - 255000, temp);
	reg = ((temp - val) + 500) / 1000;

	i2c_smbus_write_byte_data(data->client, TMP401_TEMP_CRIT_HYST,
				  reg);

	data->temp_crit_hyst = reg;

	mutex_unlock(&data->update_lock);

	return count;
}