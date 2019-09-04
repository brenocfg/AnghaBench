#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acpi_device_power_state {int /*<<< orphan*/  resources; } ;
struct TYPE_7__ {int /*<<< orphan*/  power_resources; } ;
struct TYPE_8__ {struct acpi_device_power_state* states; TYPE_3__ flags; } ;
struct TYPE_5__ {scalar_t__ valid; } ;
struct TYPE_6__ {int /*<<< orphan*/  resources; TYPE_1__ flags; } ;
struct acpi_device {TYPE_4__ power; TYPE_2__ wakeup; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3_HOT ; 
 int /*<<< orphan*/  acpi_power_resources_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_free_power_resources_lists(struct acpi_device *device)
{
	int i;

	if (device->wakeup.flags.valid)
		acpi_power_resources_list_free(&device->wakeup.resources);

	if (!device->power.flags.power_resources)
		return;

	for (i = ACPI_STATE_D0; i <= ACPI_STATE_D3_HOT; i++) {
		struct acpi_device_power_state *ps = &device->power.states[i];
		acpi_power_resources_list_free(&ps->resources);
	}
}