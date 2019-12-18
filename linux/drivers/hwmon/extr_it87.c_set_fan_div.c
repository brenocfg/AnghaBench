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
struct sensor_device_attribute {int index; } ;
struct it87_data {unsigned long** fan; int* fan_div; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int) ; 
 int DIV_TO_REG (unsigned long) ; 
 size_t EINVAL ; 
 int FAN_FROM_REG (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long FAN_TO_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IT87_REG_FAN_DIV ; 
 int /*<<< orphan*/ * IT87_REG_FAN_MIN ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 int it87_read_value (struct it87_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_div(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	struct it87_data *data = dev_get_drvdata(dev);
	int nr = sensor_attr->index;
	unsigned long val;
	int min;
	u8 old;

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	old = it87_read_value(data, IT87_REG_FAN_DIV);

	/* Save fan min limit */
	min = FAN_FROM_REG(data->fan[nr][1], DIV_FROM_REG(data->fan_div[nr]));

	switch (nr) {
	case 0:
	case 1:
		data->fan_div[nr] = DIV_TO_REG(val);
		break;
	case 2:
		if (val < 8)
			data->fan_div[nr] = 1;
		else
			data->fan_div[nr] = 3;
	}
	val = old & 0x80;
	val |= (data->fan_div[0] & 0x07);
	val |= (data->fan_div[1] & 0x07) << 3;
	if (data->fan_div[2] == 3)
		val |= 0x1 << 6;
	it87_write_value(data, IT87_REG_FAN_DIV, val);

	/* Restore fan min limit */
	data->fan[nr][1] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_div[nr]));
	it87_write_value(data, IT87_REG_FAN_MIN[nr], data->fan[nr][1]);

	mutex_unlock(&data->update_lock);
	return count;
}