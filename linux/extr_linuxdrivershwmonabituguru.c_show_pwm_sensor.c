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
struct abituguru_data {int* bank1_sensors; int** bank1_address; int** pwm_settings; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t ABIT_UGURU_TEMP_SENSOR ; 
 int /*<<< orphan*/  ENXIO ; 
 struct abituguru_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm_sensor(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct abituguru_data *data = dev_get_drvdata(dev);
	int i;
	/*
	 * We need to walk to the temp sensor addresses to find what
	 * the userspace id of the configured temp sensor is.
	 */
	for (i = 0; i < data->bank1_sensors[ABIT_UGURU_TEMP_SENSOR]; i++)
		if (data->bank1_address[ABIT_UGURU_TEMP_SENSOR][i] ==
				(data->pwm_settings[attr->index][0] & 0x0F))
			return sprintf(buf, "%d\n", i+1);

	return -ENXIO;
}