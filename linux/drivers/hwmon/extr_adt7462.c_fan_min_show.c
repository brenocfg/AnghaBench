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
typedef  int u16 ;
struct sensor_device_attribute {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7462_data {int* fan_min; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_DATA_VALID (int) ; 
 int FAN_PERIOD_TO_RPM (int) ; 
 struct adt7462_data* adt7462_update_device (struct device*) ; 
 int /*<<< orphan*/  fan_enabled (struct adt7462_data*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_show(struct device *dev,
			    struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7462_data *data = adt7462_update_device(dev);
	u16 temp;

	/* Only the MSB of the min fan period is stored... */
	temp = data->fan_min[attr->index];
	temp <<= 8;

	if (!fan_enabled(data, attr->index) ||
	    !FAN_DATA_VALID(temp))
		return sprintf(buf, "0\n");

	return sprintf(buf, "%d\n", FAN_PERIOD_TO_RPM(temp));
}