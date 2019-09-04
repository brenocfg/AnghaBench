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
typedef  int u32 ;
struct w83793_data {int pwm_default; int temp_critical; int /*<<< orphan*/  pwm_downtime; int /*<<< orphan*/  pwm_uptime; } ;
struct sensor_device_attribute_2 {int nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int SETUP_PWM_DEFAULT ; 
 int SETUP_PWM_DOWNTIME ; 
 int SETUP_PWM_UPTIME ; 
 int SETUP_TEMP_CRITICAL ; 
 int TEMP_FROM_REG (int) ; 
 int TIME_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 struct w83793_data* w83793_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_sf_setup(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	struct w83793_data *data = w83793_update_device(dev);
	u32 val = 0;

	if (nr == SETUP_PWM_DEFAULT)
		val = (data->pwm_default & 0x3f) << 2;
	else if (nr == SETUP_PWM_UPTIME)
		val = TIME_FROM_REG(data->pwm_uptime);
	else if (nr == SETUP_PWM_DOWNTIME)
		val = TIME_FROM_REG(data->pwm_downtime);
	else if (nr == SETUP_TEMP_CRITICAL)
		val = TEMP_FROM_REG(data->temp_critical & 0x7f);

	return sprintf(buf, "%d\n", val);
}