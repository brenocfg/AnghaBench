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
struct ina3221_data {int* shunt_resistors; int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int clamp_val (int,int,int) ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 unsigned int* register_channel ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ina3221_set_current(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct sensor_device_attribute *sd_attr = to_sensor_dev_attr(attr);
	struct ina3221_data *ina = dev_get_drvdata(dev);
	unsigned int reg = sd_attr->index;
	unsigned int channel = register_channel[reg];
	int resistance_uo = ina->shunt_resistors[channel];
	int val, current_ma, voltage_uv, ret;

	ret = kstrtoint(buf, 0, &current_ma);
	if (ret)
		return ret;

	/* clamp current */
	current_ma = clamp_val(current_ma,
			       INT_MIN / resistance_uo,
			       INT_MAX / resistance_uo);

	voltage_uv = DIV_ROUND_CLOSEST(current_ma * resistance_uo, 1000);

	/* clamp voltage */
	voltage_uv = clamp_val(voltage_uv, -163800, 163800);

	/* 1 / 40uV(scale) << 3(register shift) = 5 */
	val = DIV_ROUND_CLOSEST(voltage_uv, 5) & 0xfff8;

	ret = regmap_write(ina->regmap, reg, val);
	if (ret)
		return ret;

	return count;
}