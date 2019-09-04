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
typedef  int u32 ;
struct acpi_thermal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_class; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__ pnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_THERMAL_NOTIFY_DEVICES 130 
#define  ACPI_THERMAL_NOTIFY_TEMPERATURE 129 
#define  ACPI_THERMAL_NOTIFY_THRESHOLDS 128 
 int /*<<< orphan*/  ACPI_TRIPS_REFRESH_DEVICES ; 
 int /*<<< orphan*/  ACPI_TRIPS_REFRESH_THRESHOLDS ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct acpi_thermal* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_thermal_check (struct acpi_thermal*) ; 
 int /*<<< orphan*/  acpi_thermal_trips_update (struct acpi_thermal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_thermal_notify(struct acpi_device *device, u32 event)
{
	struct acpi_thermal *tz = acpi_driver_data(device);


	if (!tz)
		return;

	switch (event) {
	case ACPI_THERMAL_NOTIFY_TEMPERATURE:
		acpi_thermal_check(tz);
		break;
	case ACPI_THERMAL_NOTIFY_THRESHOLDS:
		acpi_thermal_trips_update(tz, ACPI_TRIPS_REFRESH_THRESHOLDS);
		acpi_thermal_check(tz);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
		break;
	case ACPI_THERMAL_NOTIFY_DEVICES:
		acpi_thermal_trips_update(tz, ACPI_TRIPS_REFRESH_DEVICES);
		acpi_thermal_check(tz);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
		break;
	default:
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Unsupported event [0x%x]\n", event));
		break;
	}
}