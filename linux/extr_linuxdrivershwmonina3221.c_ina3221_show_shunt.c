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
struct ina3221_data {unsigned int* shunt_resistors; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ina3221_show_shunt(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute *sd_attr = to_sensor_dev_attr(attr);
	struct ina3221_data *ina = dev_get_drvdata(dev);
	unsigned int channel = sd_attr->index;
	unsigned int resistance_uo;

	resistance_uo = ina->shunt_resistors[channel];

	return snprintf(buf, PAGE_SIZE, "%d\n", resistance_uo);
}