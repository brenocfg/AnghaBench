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
struct adt7462_data {int* alarms; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ADT7462_ALARM_FLAG_MASK ; 
 int ADT7462_ALARM_REG_SHIFT ; 
 struct adt7462_data* adt7462_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_alarm(struct device *dev,
			  struct device_attribute *devattr,
			  char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7462_data *data = adt7462_update_device(dev);
	int reg = attr->index >> ADT7462_ALARM_REG_SHIFT;
	int mask = attr->index & ADT7462_ALARM_FLAG_MASK;

	if (data->alarms[reg] & mask)
		return sprintf(buf, "1\n");
	else
		return sprintf(buf, "0\n");
}