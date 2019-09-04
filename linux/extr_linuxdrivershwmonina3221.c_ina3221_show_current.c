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
struct sensor_device_attribute {unsigned int index; } ;
struct ina3221_data {int* shunt_resistors; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
 int ina3221_read_value (struct ina3221_data*,unsigned int,int*) ; 
 unsigned int* register_channel ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ina3221_show_current(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute *sd_attr = to_sensor_dev_attr(attr);
	struct ina3221_data *ina = dev_get_drvdata(dev);
	unsigned int reg = sd_attr->index;
	unsigned int channel = register_channel[reg];
	int resistance_uo = ina->shunt_resistors[channel];
	int val, current_ma, voltage_nv, ret;

	ret = ina3221_read_value(ina, reg, &val);
	if (ret)
		return ret;
	voltage_nv = val * 40000;

	current_ma = DIV_ROUND_CLOSEST(voltage_nv, resistance_uo);

	return snprintf(buf, PAGE_SIZE, "%d\n", current_ma);
}