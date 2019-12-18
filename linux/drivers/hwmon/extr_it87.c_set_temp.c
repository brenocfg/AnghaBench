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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct it87_data {int** temp; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  valid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int IT87_REG_BEEP_ENABLE ; 
 int IT87_REG_TEMP_HIGH (int) ; 
 int IT87_REG_TEMP_LOW (int) ; 
 int* IT87_REG_TEMP_OFFSET ; 
 int TEMP_TO_REG (long) ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 int it87_read_value (struct it87_data*,int) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int,int) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int nr = sattr->nr;
	int index = sattr->index;
	struct it87_data *data = dev_get_drvdata(dev);
	long val;
	u8 reg, regval;

	if (kstrtol(buf, 10, &val) < 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);

	switch (index) {
	default:
	case 1:
		reg = IT87_REG_TEMP_LOW(nr);
		break;
	case 2:
		reg = IT87_REG_TEMP_HIGH(nr);
		break;
	case 3:
		regval = it87_read_value(data, IT87_REG_BEEP_ENABLE);
		if (!(regval & 0x80)) {
			regval |= 0x80;
			it87_write_value(data, IT87_REG_BEEP_ENABLE, regval);
		}
		data->valid = 0;
		reg = IT87_REG_TEMP_OFFSET[nr];
		break;
	}

	data->temp[nr][index] = TEMP_TO_REG(val);
	it87_write_value(data, reg, data->temp[nr][index]);
	mutex_unlock(&data->update_lock);
	return count;
}