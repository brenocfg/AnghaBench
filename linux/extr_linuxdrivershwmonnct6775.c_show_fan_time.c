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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct nct6775_data {int /*<<< orphan*/ * pwm_mode; int /*<<< orphan*/ ** fan_time; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct nct6775_data* nct6775_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int step_time_from_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
show_fan_time(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct nct6775_data *data = nct6775_update_device(dev);
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int nr = sattr->nr;
	int index = sattr->index;

	return sprintf(buf, "%d\n",
		       step_time_from_reg(data->fan_time[index][nr],
					  data->pwm_mode[nr]));
}