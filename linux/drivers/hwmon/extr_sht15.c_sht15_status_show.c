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
typedef  int u8 ;
struct sht15_data {int val_status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 struct sht15_data* dev_get_drvdata (struct device*) ; 
 int sht15_update_status (struct sht15_data*) ; 
 int sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t sht15_status_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	int ret;
	struct sht15_data *data = dev_get_drvdata(dev);
	u8 bit = to_sensor_dev_attr(attr)->index;

	ret = sht15_update_status(data);

	return ret ? ret : sprintf(buf, "%d\n", !!(data->val_status & bit));
}