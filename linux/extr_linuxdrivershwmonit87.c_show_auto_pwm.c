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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct it87_data {int /*<<< orphan*/ ** auto_pwm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct it87_data* it87_update_device (struct device*) ; 
 int pwm_from_reg (struct it87_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_auto_pwm(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct it87_data *data = it87_update_device(dev);
	struct sensor_device_attribute_2 *sensor_attr =
			to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int point = sensor_attr->index;

	return sprintf(buf, "%d\n",
		       pwm_from_reg(data, data->auto_pwm[nr][point]));
}