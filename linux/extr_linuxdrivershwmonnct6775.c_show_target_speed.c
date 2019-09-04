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
struct sensor_device_attribute {int index; } ;
struct nct6775_data {int /*<<< orphan*/ * fan_div; int /*<<< orphan*/ * target_speed; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int fan_from_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nct6775_data* nct6775_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
show_target_speed(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct nct6775_data *data = nct6775_update_device(dev);
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	int nr = sattr->index;

	return sprintf(buf, "%d\n",
		       fan_from_reg16(data->target_speed[nr],
				      data->fan_div[nr]));
}