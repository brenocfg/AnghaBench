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
struct aspeed_pwm_tacho_data {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int aspeed_get_fan_tach_ch_rpm (struct aspeed_pwm_tacho_data*,int) ; 
 struct aspeed_pwm_tacho_data* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t rpm_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int index = sensor_attr->index;
	int rpm;
	struct aspeed_pwm_tacho_data *priv = dev_get_drvdata(dev);

	rpm = aspeed_get_fan_tach_ch_rpm(priv, index);
	if (rpm < 0)
		return rpm;

	return sprintf(buf, "%d\n", rpm);
}