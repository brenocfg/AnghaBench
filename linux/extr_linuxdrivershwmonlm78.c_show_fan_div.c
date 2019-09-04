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
struct sensor_device_attribute {size_t index; } ;
struct lm78_data {int /*<<< orphan*/ * fan_div; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 struct lm78_data* lm78_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_fan_div(struct device *dev, struct device_attribute *da,
			    char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct lm78_data *data = lm78_update_device(dev);
	return sprintf(buf, "%d\n", DIV_FROM_REG(data->fan_div[attr->index]));
}