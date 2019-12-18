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
struct thermal_data {int /*<<< orphan*/  regmap; } ;
struct sensor_device_attribute_2 {unsigned int index; int /*<<< orphan*/  nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct thermal_data* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t bit_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct sensor_device_attribute_2 *sda = to_sensor_dev_attr_2(attr);
	struct thermal_data *data = dev_get_drvdata(dev);
	unsigned int val;
	int retval;

	retval = regmap_read(data->regmap, sda->nr, &val);
	if (retval < 0)
		return retval;
	return sprintf(buf, "%d\n", !!(val & sda->index));
}