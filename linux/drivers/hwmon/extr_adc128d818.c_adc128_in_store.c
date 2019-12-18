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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adc128_data {int** in; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 int ADC128_REG_IN_MAX (int) ; 
 int ADC128_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (long,int) ; 
 int clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adc128_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t adc128_in_store(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t count)
{
	struct adc128_data *data = dev_get_drvdata(dev);
	int index = to_sensor_dev_attr_2(attr)->index;
	int nr = to_sensor_dev_attr_2(attr)->nr;
	u8 reg, regval;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err < 0)
		return err;

	mutex_lock(&data->update_lock);
	/* 10 mV LSB on limit registers */
	regval = clamp_val(DIV_ROUND_CLOSEST(val, 10), 0, 255);
	data->in[index][nr] = regval << 4;
	reg = index == 1 ? ADC128_REG_IN_MIN(nr) : ADC128_REG_IN_MAX(nr);
	i2c_smbus_write_byte_data(data->client, reg, regval);
	mutex_unlock(&data->update_lock);

	return count;
}