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
struct acpi_power_meter_resource {int* trip; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  lock; struct acpi_device* acpi_dev; scalar_t__ sensors_valid; } ;
struct acpi_device {int /*<<< orphan*/  dev; struct acpi_power_meter_resource* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_POWER_METER_CLASS ; 
 int /*<<< orphan*/  ACPI_POWER_METER_DEVICE_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  free_capabilities (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  hwmon_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct acpi_power_meter_resource*) ; 
 struct acpi_power_meter_resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int read_capabilities (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  remove_attrs (struct acpi_power_meter_resource*) ; 
 int setup_attrs (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_power_meter_add(struct acpi_device *device)
{
	int res;
	struct acpi_power_meter_resource *resource;

	if (!device)
		return -EINVAL;

	resource = kzalloc(sizeof(struct acpi_power_meter_resource),
			   GFP_KERNEL);
	if (!resource)
		return -ENOMEM;

	resource->sensors_valid = 0;
	resource->acpi_dev = device;
	mutex_init(&resource->lock);
	strcpy(acpi_device_name(device), ACPI_POWER_METER_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_POWER_METER_CLASS);
	device->driver_data = resource;

	free_capabilities(resource);
	res = read_capabilities(resource);
	if (res)
		goto exit_free;

	resource->trip[0] = resource->trip[1] = -1;

	res = setup_attrs(resource);
	if (res)
		goto exit_free;

	resource->hwmon_dev = hwmon_device_register(&device->dev);
	if (IS_ERR(resource->hwmon_dev)) {
		res = PTR_ERR(resource->hwmon_dev);
		goto exit_remove;
	}

	res = 0;
	goto exit;

exit_remove:
	remove_attrs(resource);
exit_free:
	kfree(resource);
exit:
	return res;
}