#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sensor_device_attribute_2 {int nr; int index; } ;
struct f71805f_data {TYPE_1__* auto_points; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/ * temp; } ;

/* Variables and functions */
 struct f71805f_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temp_from_reg (int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm_auto_point_temp(struct device *dev,
					struct device_attribute *devattr,
					char *buf)
{
	struct f71805f_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	int pwmnr = attr->nr;
	int apnr = attr->index;

	return sprintf(buf, "%ld\n",
		       temp_from_reg(data->auto_points[pwmnr].temp[apnr]));
}