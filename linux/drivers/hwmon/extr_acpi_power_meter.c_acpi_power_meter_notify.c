#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct acpi_power_meter_resource {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct acpi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_POWER_METER_CLASS ; 
#define  METER_NOTIFY_CAP 132 
#define  METER_NOTIFY_CAPPING 131 
#define  METER_NOTIFY_CONFIG 130 
#define  METER_NOTIFY_INTERVAL 129 
#define  METER_NOTIFY_TRIP 128 
 int /*<<< orphan*/  POWER_ALARM_NAME ; 
 int /*<<< orphan*/  POWER_AVERAGE_NAME ; 
 int /*<<< orphan*/  POWER_AVG_INTERVAL_NAME ; 
 int /*<<< orphan*/  POWER_CAP_NAME ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct acpi_power_meter_resource* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  free_capabilities (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_capabilities (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  remove_attrs (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  setup_attrs (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_avg_interval (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  update_cap (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  update_meter (struct acpi_power_meter_resource*) ; 

__attribute__((used)) static void acpi_power_meter_notify(struct acpi_device *device, u32 event)
{
	struct acpi_power_meter_resource *resource;
	int res;

	if (!device || !acpi_driver_data(device))
		return;

	resource = acpi_driver_data(device);

	mutex_lock(&resource->lock);
	switch (event) {
	case METER_NOTIFY_CONFIG:
		free_capabilities(resource);
		res = read_capabilities(resource);
		if (res)
			break;

		remove_attrs(resource);
		setup_attrs(resource);
		break;
	case METER_NOTIFY_TRIP:
		sysfs_notify(&device->dev.kobj, NULL, POWER_AVERAGE_NAME);
		update_meter(resource);
		break;
	case METER_NOTIFY_CAP:
		sysfs_notify(&device->dev.kobj, NULL, POWER_CAP_NAME);
		update_cap(resource);
		break;
	case METER_NOTIFY_INTERVAL:
		sysfs_notify(&device->dev.kobj, NULL, POWER_AVG_INTERVAL_NAME);
		update_avg_interval(resource);
		break;
	case METER_NOTIFY_CAPPING:
		sysfs_notify(&device->dev.kobj, NULL, POWER_ALARM_NAME);
		dev_info(&device->dev, "Capping in progress.\n");
		break;
	default:
		WARN(1, "Unexpected event %d\n", event);
		break;
	}
	mutex_unlock(&resource->lock);

	acpi_bus_generate_netlink_event(ACPI_POWER_METER_CLASS,
					dev_name(&device->dev), event, 0);
}