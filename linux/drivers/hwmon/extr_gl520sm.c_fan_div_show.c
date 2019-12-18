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
struct gl520_data {int /*<<< orphan*/ * fan_div; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 struct gl520_data* gl520_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_div_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	int n = to_sensor_dev_attr(attr)->index;
	struct gl520_data *data = gl520_update_device(dev);

	return sprintf(buf, "%d\n", DIV_FROM_REG(data->fan_div[n]));
}