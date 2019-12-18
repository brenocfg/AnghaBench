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
struct thermal_data {int /*<<< orphan*/  mutex; struct regmap* regmap; } ;
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct regmap {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
 int clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct thermal_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct regmap*,int,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t hyst_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	struct thermal_data *data = dev_get_drvdata(dev);
	struct regmap *regmap = data->regmap;
	unsigned int limit;
	int retval;
	int hyst;
	unsigned long val;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->mutex);
	retval = regmap_read(regmap, sda->index, &limit);
	if (retval < 0)
		goto fail;

	hyst = limit * 1000 - val;
	hyst = clamp_val(DIV_ROUND_CLOSEST(hyst, 1000), 0, 255);
	retval = regmap_write(regmap, 0x21, hyst);
	if (retval == 0)
		retval = count;
fail:
	mutex_unlock(&data->mutex);
	return retval;
}