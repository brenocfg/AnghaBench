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
struct fts_data {int fan_alarm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int BIT (int) ; 
 struct fts_data* dev_get_drvdata (struct device*) ; 
 int fts_update_device (struct fts_data*) ; 
 int sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_alarm_show(struct device *dev,
			      struct device_attribute *devattr, char *buf)
{
	struct fts_data *data = dev_get_drvdata(dev);
	int index = to_sensor_dev_attr(devattr)->index;
	int err;

	err = fts_update_device(data);
	if (err < 0)
		return err;

	return sprintf(buf, "%d\n", !!(data->fan_alarm & BIT(index)));
}