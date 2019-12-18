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
struct ina3221_input {int shunt_resistor; } ;
struct ina3221_data {struct ina3221_input* inputs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int clamp_val (int,int,int /*<<< orphan*/ ) ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ina3221_shunt_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct sensor_device_attribute *sd_attr = to_sensor_dev_attr(attr);
	struct ina3221_data *ina = dev_get_drvdata(dev);
	unsigned int channel = sd_attr->index;
	struct ina3221_input *input = &ina->inputs[channel];
	int val;
	int ret;

	ret = kstrtoint(buf, 0, &val);
	if (ret)
		return ret;

	val = clamp_val(val, 1, INT_MAX);

	input->shunt_resistor = val;

	return count;
}