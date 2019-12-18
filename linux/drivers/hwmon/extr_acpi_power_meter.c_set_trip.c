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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_power_meter_resource {unsigned long* trip; int /*<<< orphan*/  lock; } ;
struct acpi_device {struct acpi_power_meter_resource* driver_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_acpi_trip (struct acpi_power_meter_resource*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_trip(struct device *dev, struct device_attribute *devattr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_power_meter_resource *resource = acpi_dev->driver_data;
	int res;
	unsigned long temp;

	res = kstrtoul(buf, 10, &temp);
	if (res)
		return res;

	temp = DIV_ROUND_CLOSEST(temp, 1000);

	mutex_lock(&resource->lock);
	resource->trip[attr->index - 7] = temp;
	res = set_acpi_trip(resource);
	mutex_unlock(&resource->lock);

	if (res)
		return res;

	return count;
}