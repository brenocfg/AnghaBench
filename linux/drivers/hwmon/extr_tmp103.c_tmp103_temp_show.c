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
struct regmap {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct regmap* dev_get_drvdata (struct device*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int sprintf (char*,char*,int) ; 
 int tmp103_reg_to_mc (unsigned int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t tmp103_temp_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	struct regmap *regmap = dev_get_drvdata(dev);
	unsigned int regval;
	int ret;

	ret = regmap_read(regmap, sda->index, &regval);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d\n", tmp103_reg_to_mc(regval));
}