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
struct adm1025_data {int /*<<< orphan*/ * in_max; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int IN_FROM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adm1025_data* adm1025_update_device (struct device*) ; 
 int /*<<< orphan*/ * in_scale ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
in_max_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int index = to_sensor_dev_attr(attr)->index;
	struct adm1025_data *data = adm1025_update_device(dev);
	return sprintf(buf, "%u\n", IN_FROM_REG(data->in_max[index],
		       in_scale[index]));
}