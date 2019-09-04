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
struct f71882fg_data {int fan_status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 struct f71882fg_data* f71882fg_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_fan_alarm(struct device *dev, struct device_attribute
	*devattr, char *buf)
{
	struct f71882fg_data *data = f71882fg_update_device(dev);
	int nr = to_sensor_dev_attr_2(devattr)->index;

	if (data->fan_status & (1 << nr))
		return sprintf(buf, "1\n");
	else
		return sprintf(buf, "0\n");
}