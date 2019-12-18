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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amc6821_data {int* fan; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 struct amc6821_data* amc6821_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_show(struct device *dev, struct device_attribute *devattr,
			char *buf)
{
	struct amc6821_data *data = amc6821_update_device(dev);
	int ix = to_sensor_dev_attr(devattr)->index;
	if (0 == data->fan[ix])
		return sprintf(buf, "0");
	return sprintf(buf, "%d\n", (int)(6000000 / data->fan[ix]));
}