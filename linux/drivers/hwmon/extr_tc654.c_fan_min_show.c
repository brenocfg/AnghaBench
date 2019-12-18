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
struct tc654_data {int /*<<< orphan*/ * fan_fault; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tc654_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct tc654_data*) ; 
 int TC654_FAN_FAULT_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct tc654_data* tc654_update_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_show(struct device *dev, struct device_attribute *da,
			    char *buf)
{
	int nr = to_sensor_dev_attr(da)->index;
	struct tc654_data *data = tc654_update_client(dev);

	if (IS_ERR(data))
		return PTR_ERR(data);

	return sprintf(buf, "%d\n",
		       TC654_FAN_FAULT_FROM_REG(data->fan_fault[nr]));
}