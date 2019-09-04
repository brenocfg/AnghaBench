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
struct acpi_power_meter_resource {char* model_number; char* serial_number; char* oem_info; } ;
struct acpi_device {struct acpi_power_meter_resource* driver_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  char* acpi_string ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_str(struct device *dev,
			struct device_attribute *devattr,
			char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_power_meter_resource *resource = acpi_dev->driver_data;
	acpi_string val;

	switch (attr->index) {
	case 0:
		val = resource->model_number;
		break;
	case 1:
		val = resource->serial_number;
		break;
	case 2:
		val = resource->oem_info;
		break;
	default:
		WARN(1, "Implementation error: unexpected attribute index %d\n",
		     attr->index);
		val = "";
		break;
	}

	return sprintf(buf, "%s\n", val);
}