#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int match_driver; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__ flags; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUS_TYPE_POWER_BUTTON ; 
 int /*<<< orphan*/  ACPI_BUS_TYPE_SLEEP_BUTTON ; 
 int ACPI_FADT_POWER_BUTTON ; 
 int ACPI_FADT_SLEEP_BUTTON ; 
 int /*<<< orphan*/  ACPI_STA_DEFAULT ; 
 int acpi_add_single_object (struct acpi_device**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ acpi_gbl_FADT ; 
 int device_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int acpi_bus_scan_fixed(void)
{
	int result = 0;

	/*
	 * Enumerate all fixed-feature devices.
	 */
	if (!(acpi_gbl_FADT.flags & ACPI_FADT_POWER_BUTTON)) {
		struct acpi_device *device = NULL;

		result = acpi_add_single_object(&device, NULL,
						ACPI_BUS_TYPE_POWER_BUTTON,
						ACPI_STA_DEFAULT);
		if (result)
			return result;

		device->flags.match_driver = true;
		result = device_attach(&device->dev);
		if (result < 0)
			return result;

		device_init_wakeup(&device->dev, true);
	}

	if (!(acpi_gbl_FADT.flags & ACPI_FADT_SLEEP_BUTTON)) {
		struct acpi_device *device = NULL;

		result = acpi_add_single_object(&device, NULL,
						ACPI_BUS_TYPE_SLEEP_BUTTON,
						ACPI_STA_DEFAULT);
		if (result)
			return result;

		device->flags.match_driver = true;
		result = device_attach(&device->dev);
	}

	return result < 0 ? result : 0;
}