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
struct thermal_data {struct regmap* regmap; } ;
struct sensor_device_attribute {int index; } ;
struct regmap {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct thermal_data* dev_get_drvdata (struct device*) ; 
 int regmap_read (struct regmap*,int,unsigned int*) ; 
 int sprintf (char*,char*,unsigned int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_hyst_common(struct device *dev,
				struct device_attribute *attr, char *buf,
				bool is_min)
{
	struct sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	struct thermal_data *data = dev_get_drvdata(dev);
	struct regmap *regmap = data->regmap;
	unsigned int limit;
	unsigned int hyst;
	int retval;

	retval = regmap_read(regmap, sda->index, &limit);
	if (retval < 0)
		return retval;

	retval = regmap_read(regmap, 0x21, &hyst);
	if (retval < 0)
		return retval;

	return sprintf(buf, "%d000\n", is_min ? limit + hyst : limit - hyst);
}