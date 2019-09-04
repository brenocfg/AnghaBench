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
struct sensor_device_attribute_2 {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct abituguru_data {int* bank2_value; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ABIT_UGURU_FAN_MAX ; 
 int /*<<< orphan*/  EIO ; 
 struct abituguru_data* abituguru_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_bank2_value(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct abituguru_data *data = abituguru_update_device(dev);
	if (!data)
		return -EIO;
	return sprintf(buf, "%d\n", (data->bank2_value[attr->index] *
		ABIT_UGURU_FAN_MAX + 128) / 255);
}