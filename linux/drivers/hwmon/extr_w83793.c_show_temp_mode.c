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
typedef  int u8 ;
struct w83793_data {int* temp_mode; } ;
struct sensor_device_attribute_2 {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int* TO_TEMP_MODE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 struct w83793_data* w83793_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_temp_mode(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct w83793_data *data = w83793_update_device(dev);
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int index = sensor_attr->index;
	u8 mask = (index < 4) ? 0x03 : 0x01;
	u8 shift = (index < 4) ? (2 * index) : (index - 4);
	u8 tmp;
	index = (index < 4) ? 0 : 1;

	tmp = (data->temp_mode[index] >> shift) & mask;

	/* for the internal sensor, found out if diode or thermistor */
	if (tmp == 1)
		tmp = index == 0 ? 3 : 4;
	else
		tmp = TO_TEMP_MODE[tmp];

	return sprintf(buf, "%d\n", tmp);
}