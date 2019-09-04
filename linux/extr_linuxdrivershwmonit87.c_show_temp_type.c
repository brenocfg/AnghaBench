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
struct sensor_device_attribute {int index; } ;
struct it87_data {int sensor; int extra; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ has_temp_old_peci (struct it87_data*,int) ; 
 scalar_t__ has_temp_peci (struct it87_data*,int) ; 
 struct it87_data* it87_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp_type(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	struct it87_data *data = it87_update_device(dev);
	u8 reg = data->sensor;	    /* In case value is updated while used */
	u8 extra = data->extra;

	if ((has_temp_peci(data, nr) && (reg >> 6 == nr + 1)) ||
	    (has_temp_old_peci(data, nr) && (extra & 0x80)))
		return sprintf(buf, "6\n");  /* Intel PECI */
	if (reg & (1 << nr))
		return sprintf(buf, "3\n");  /* thermal diode */
	if (reg & (8 << nr))
		return sprintf(buf, "4\n");  /* thermistor */
	return sprintf(buf, "0\n");      /* disabled */
}