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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adc128_data {int* temp; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;
typedef  int s8 ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC128_REG_TEMP_HYST ; 
 int /*<<< orphan*/  ADC128_REG_TEMP_MAX ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (long,int) ; 
 int clamp_val (int /*<<< orphan*/ ,int,int) ; 
 struct adc128_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t adc128_temp_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct adc128_data *data = dev_get_drvdata(dev);
	int index = to_sensor_dev_attr(attr)->index;
	long val;
	int err;
	s8 regval;

	err = kstrtol(buf, 10, &val);
	if (err < 0)
		return err;

	mutex_lock(&data->update_lock);
	regval = clamp_val(DIV_ROUND_CLOSEST(val, 1000), -128, 127);
	data->temp[index] = regval << 1;
	i2c_smbus_write_byte_data(data->client,
				  index == 1 ? ADC128_REG_TEMP_MAX
					     : ADC128_REG_TEMP_HYST,
				  regval);
	mutex_unlock(&data->update_lock);

	return count;
}