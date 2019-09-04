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
struct f71805f_data {int /*<<< orphan*/ * in_high; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct f71805f_data* f71805f_update_device (struct device*) ; 
 int /*<<< orphan*/  in_from_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_in_max(struct device *dev, struct device_attribute
			   *devattr, char *buf)
{
	struct f71805f_data *data = f71805f_update_device(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int nr = attr->index;

	return sprintf(buf, "%ld\n", in_from_reg(data->in_high[nr]));
}