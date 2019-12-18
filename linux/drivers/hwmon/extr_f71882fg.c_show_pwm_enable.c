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
struct f71882fg_data {int pwm_enable; int /*<<< orphan*/  type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 struct f71882fg_data* f71882fg_update_device (struct device*) ; 
 int /*<<< orphan*/  f8000 ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm_enable(struct device *dev,
			       struct device_attribute *devattr, char *buf)
{
	int result = 0;
	struct f71882fg_data *data = f71882fg_update_device(dev);
	int nr = to_sensor_dev_attr_2(devattr)->index;

	switch ((data->pwm_enable >> 2 * nr) & 3) {
	case 0:
	case 1:
		result = 2; /* Normal auto mode */
		break;
	case 2:
		result = 1; /* Manual mode */
		break;
	case 3:
		if (data->type == f8000)
			result = 3; /* Thermostat mode */
		else
			result = 1; /* Manual mode */
		break;
	}

	return sprintf(buf, "%d\n", result);
}