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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int accuracy; } ;
struct acpi_power_meter_resource {TYPE_1__ caps; } ;
struct acpi_device {struct acpi_power_meter_resource* driver_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,unsigned int) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t show_accuracy(struct device *dev,
			     struct device_attribute *devattr,
			     char *buf)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_power_meter_resource *resource = acpi_dev->driver_data;
	unsigned int acc = resource->caps.accuracy;

	return sprintf(buf, "%u.%u%%\n", acc / 1000, acc % 1000);
}