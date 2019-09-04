#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ power_resources; } ;
struct TYPE_5__ {int state; TYPE_1__ flags; } ;
struct TYPE_6__ {int initialized; } ;
struct acpi_device {TYPE_2__ power; TYPE_3__ flags; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3_COLD ; 
 int ACPI_STATE_UNKNOWN ; 
 int EINVAL ; 
 int ENXIO ; 
 int acpi_dev_pm_explicit_set (struct acpi_device*,int) ; 
 int acpi_device_get_power (struct acpi_device*,int*) ; 
 int /*<<< orphan*/  acpi_device_is_present (struct acpi_device*) ; 
 int acpi_power_on_resources (struct acpi_device*,int) ; 

int acpi_bus_init_power(struct acpi_device *device)
{
	int state;
	int result;

	if (!device)
		return -EINVAL;

	device->power.state = ACPI_STATE_UNKNOWN;
	if (!acpi_device_is_present(device)) {
		device->flags.initialized = false;
		return -ENXIO;
	}

	result = acpi_device_get_power(device, &state);
	if (result)
		return result;

	if (state < ACPI_STATE_D3_COLD && device->power.flags.power_resources) {
		/* Reference count the power resources. */
		result = acpi_power_on_resources(device, state);
		if (result)
			return result;

		if (state == ACPI_STATE_D0) {
			/*
			 * If _PSC is not present and the state inferred from
			 * power resources appears to be D0, it still may be
			 * necessary to execute _PS0 at this point, because
			 * another device using the same power resources may
			 * have been put into D0 previously and that's why we
			 * see D0 here.
			 */
			result = acpi_dev_pm_explicit_set(device, state);
			if (result)
				return result;
		}
	} else if (state == ACPI_STATE_UNKNOWN) {
		/*
		 * No power resources and missing _PSC?  Cross fingers and make
		 * it D0 in hope that this is what the BIOS put the device into.
		 * [We tried to force D0 here by executing _PS0, but that broke
		 * Toshiba P870-303 in a nasty way.]
		 */
		state = ACPI_STATE_D0;
	}
	device->power.state = state;
	return 0;
}