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
struct w83795_data {int* temp_read_vrlsb; int /*<<< orphan*/ ** temp; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int TEMP_READ ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 long temp_from_reg (int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 struct w83795_data* w83795_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_temp(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	struct w83795_data *data = w83795_update_device(dev);
	long temp = temp_from_reg(data->temp[index][nr]);

	if (nr == TEMP_READ)
		temp += (data->temp_read_vrlsb[index] >> 6) * 250;
	return sprintf(buf, "%ld\n", temp);
}