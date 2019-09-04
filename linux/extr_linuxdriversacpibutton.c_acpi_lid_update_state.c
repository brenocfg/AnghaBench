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
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int acpi_lid_evaluate_state (struct acpi_device*) ; 
 int acpi_lid_notify_state (struct acpi_device*,int) ; 
 int /*<<< orphan*/  acpi_pm_wakeup_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_lid_update_state(struct acpi_device *device,
				 bool signal_wakeup)
{
	int state;

	state = acpi_lid_evaluate_state(device);
	if (state < 0)
		return state;

	if (state && signal_wakeup)
		acpi_pm_wakeup_event(&device->dev);

	return acpi_lid_notify_state(device, state);
}