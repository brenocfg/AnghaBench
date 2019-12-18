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
struct smsc47m1_data {int* pwm; int /*<<< orphan*/ * fan_preload; int /*<<< orphan*/ * fan_div; int /*<<< orphan*/ * fan; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int FAN_FROM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smsc47m1_data* smsc47m1_update_device (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_show(struct device *dev, struct device_attribute *devattr,
			char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	int nr = attr->index;
	/*
	 * This chip (stupidly) stops monitoring fan speed if PWM is
	 * enabled and duty cycle is 0%. This is fine if the monitoring
	 * and control concern the same fan, but troublesome if they are
	 * not (which could as well happen).
	 */
	int rpm = (data->pwm[nr] & 0x7F) == 0x00 ? 0 :
		  FAN_FROM_REG(data->fan[nr],
			       DIV_FROM_REG(data->fan_div[nr]),
			       data->fan_preload[nr]);
	return sprintf(buf, "%d\n", rpm);
}