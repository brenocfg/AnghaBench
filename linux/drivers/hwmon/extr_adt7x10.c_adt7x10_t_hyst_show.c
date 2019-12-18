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
struct adt7x10_data {int hyst; int /*<<< orphan*/ * temp; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ADT7X10_REG_TO_TEMP (struct adt7x10_data*,int /*<<< orphan*/ ) ; 
 int ADT7X10_T_HYST_MASK ; 
 struct adt7x10_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t adt7x10_t_hyst_show(struct device *dev,
				   struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct adt7x10_data *data = dev_get_drvdata(dev);
	int nr = attr->index;
	int hyst;

	hyst = (data->hyst & ADT7X10_T_HYST_MASK) * 1000;

	/*
	 * hysteresis is stored as a 4 bit offset in the device, convert it
	 * to an absolute value
	 */
	if (nr == 2)	/* min has positive offset, others have negative */
		hyst = -hyst;
	return sprintf(buf, "%d\n",
		       ADT7X10_REG_TO_TEMP(data, data->temp[nr]) - hyst);
}