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
struct sensor_device_attribute_2 {int /*<<< orphan*/  index; int /*<<< orphan*/  nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct thermal_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t bit_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sda = to_sensor_dev_attr_2(attr);
	struct thermal_data *data = dev_get_drvdata(dev);
	unsigned long val;
	int retval;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;

	retval = regmap_update_bits(data->regmap, sda->nr, sda->index,
				    val ? sda->index : 0);
	if (retval < 0)
		return retval;
	return count;
}