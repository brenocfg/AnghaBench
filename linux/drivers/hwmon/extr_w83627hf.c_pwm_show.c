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
struct w83627hf_data {scalar_t__* pwm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 struct w83627hf_data* w83627hf_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
pwm_show(struct device *dev, struct device_attribute *devattr, char *buf)
{
	int nr = to_sensor_dev_attr(devattr)->index;
	struct w83627hf_data *data = w83627hf_update_device(dev);
	return sprintf(buf, "%ld\n", (long) data->pwm[nr]);
}