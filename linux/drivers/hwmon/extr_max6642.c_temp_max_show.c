#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sensor_device_attribute_2 {size_t nr; } ;
struct max6642_data {int /*<<< orphan*/ * temp_high; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct max6642_data* max6642_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int temp_from_reg (int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_max_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(attr);
	struct max6642_data *data = max6642_update_device(dev);

	return sprintf(buf, "%d\n", temp_from_reg(data->temp_high[attr2->nr]));
}