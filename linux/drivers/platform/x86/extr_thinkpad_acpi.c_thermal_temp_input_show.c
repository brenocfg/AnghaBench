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
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ TPACPI_THERMAL_SENSOR_NA ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int thermal_get_sensor (int,scalar_t__*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t thermal_temp_input_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct sensor_device_attribute *sensor_attr =
					to_sensor_dev_attr(attr);
	int idx = sensor_attr->index;
	s32 value;
	int res;

	res = thermal_get_sensor(idx, &value);
	if (res)
		return res;
	if (value == TPACPI_THERMAL_SENSOR_NA)
		return -ENXIO;

	return snprintf(buf, PAGE_SIZE, "%d\n", value);
}