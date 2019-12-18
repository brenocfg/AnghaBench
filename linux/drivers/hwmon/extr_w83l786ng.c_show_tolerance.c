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
struct w83l786ng_data {scalar_t__* tolerance; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 struct w83l786ng_data* w83l786ng_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_tolerance(struct device *dev, struct device_attribute *attr, char *buf)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct w83l786ng_data *data = w83l786ng_update_device(dev);
	return sprintf(buf, "%ld\n", (long)data->tolerance[nr]);
}