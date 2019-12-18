#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct emc2103_data {TYPE_1__* temp; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {int degrees; } ;

/* Variables and functions */
 struct emc2103_data* emc2103_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_2__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
temp_fault_show(struct device *dev, struct device_attribute *da, char *buf)
{
	int nr = to_sensor_dev_attr(da)->index;
	struct emc2103_data *data = emc2103_update_device(dev);
	bool fault = (data->temp[nr].degrees == -128);
	return sprintf(buf, "%d\n", fault ? 1 : 0);
}