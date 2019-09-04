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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct aem_data {int /*<<< orphan*/ * power_period; int /*<<< orphan*/  (* update ) (struct aem_data*) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct aem_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct aem_data*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t aem_show_power_period(struct device *dev,
				     struct device_attribute *devattr,
				     char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct aem_data *a = dev_get_drvdata(dev);
	a->update(a);

	return sprintf(buf, "%lu\n", a->power_period[attr->index]);
}