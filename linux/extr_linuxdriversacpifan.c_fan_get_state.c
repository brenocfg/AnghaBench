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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3_COLD ; 
 int ACPI_STATE_D3_HOT ; 
 int acpi_device_update_power (struct acpi_device*,int*) ; 

__attribute__((used)) static int fan_get_state(struct acpi_device *device, unsigned long *state)
{
	int result;
	int acpi_state = ACPI_STATE_D0;

	result = acpi_device_update_power(device, &acpi_state);
	if (result)
		return result;

	*state = acpi_state == ACPI_STATE_D3_COLD
			|| acpi_state == ACPI_STATE_D3_HOT ?
		0 : (acpi_state == ACPI_STATE_D0 ? 1 : -1);
	return 0;
}