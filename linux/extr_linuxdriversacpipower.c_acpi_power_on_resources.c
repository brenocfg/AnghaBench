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
struct TYPE_4__ {TYPE_1__* states; } ;
struct acpi_device {TYPE_2__ power; } ;
struct TYPE_3__ {int /*<<< orphan*/  resources; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3_HOT ; 
 int EINVAL ; 
 int acpi_power_on_list (int /*<<< orphan*/ *) ; 

int acpi_power_on_resources(struct acpi_device *device, int state)
{
	if (!device || state < ACPI_STATE_D0 || state > ACPI_STATE_D3_HOT)
		return -EINVAL;

	return acpi_power_on_list(&device->power.states[state].resources);
}