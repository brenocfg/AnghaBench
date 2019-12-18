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
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int powr1220_read_adc (struct device*,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t powr1220_voltage_show(struct device *dev,
				     struct device_attribute *dev_attr,
				     char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	int adc_val = powr1220_read_adc(dev, attr->index);

	if (adc_val < 0)
		return adc_val;

	return sprintf(buf, "%d\n", adc_val);
}