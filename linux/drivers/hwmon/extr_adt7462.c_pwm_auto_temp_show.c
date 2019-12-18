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
struct sensor_device_attribute {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7462_data {int* pwm_cfg; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ADT7462_PWM_CHANNEL_SHIFT ; 
 struct adt7462_data* adt7462_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwm_auto_temp_show(struct device *dev,
				  struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7462_data *data = adt7462_update_device(dev);
	int channel = data->pwm_cfg[attr->index] >> ADT7462_PWM_CHANNEL_SHIFT;

	switch (channel) {
	case 0: /* temp[1234] only */
	case 1:
	case 2:
	case 3:
		return sprintf(buf, "%d\n", (1 << channel));
	case 5: /* temp1 & temp4  */
		return sprintf(buf, "9\n");
	case 6:
		return sprintf(buf, "15\n");
	default:
		return sprintf(buf, "0\n");
	}
}