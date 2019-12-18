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
struct max6697_data {int alarms; TYPE_1__* chip; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {int* alarm_map; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct max6697_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct max6697_data*) ; 
 struct max6697_data* max6697_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_2__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t alarm_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	int index = to_sensor_dev_attr(attr)->index;
	struct max6697_data *data = max6697_update_device(dev);

	if (IS_ERR(data))
		return PTR_ERR(data);

	if (data->chip->alarm_map)
		index = data->chip->alarm_map[index];

	return sprintf(buf, "%u\n", (data->alarms >> index) & 0x1);
}