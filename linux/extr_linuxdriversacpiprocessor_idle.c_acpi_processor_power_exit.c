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
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ power_setup_done; scalar_t__ power; } ;
struct acpi_processor {TYPE_1__ flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_cpuidle_device ; 
 int /*<<< orphan*/  acpi_idle_driver ; 
 scalar_t__ acpi_processor_registered ; 
 int /*<<< orphan*/  cpuidle_unregister_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_unregister_driver (int /*<<< orphan*/ *) ; 
 scalar_t__ disabled_by_idle_boot_param () ; 
 struct cpuidle_device* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int acpi_processor_power_exit(struct acpi_processor *pr)
{
	struct cpuidle_device *dev = per_cpu(acpi_cpuidle_device, pr->id);

	if (disabled_by_idle_boot_param())
		return 0;

	if (pr->flags.power) {
		cpuidle_unregister_device(dev);
		acpi_processor_registered--;
		if (acpi_processor_registered == 0)
			cpuidle_unregister_driver(&acpi_idle_driver);
	}

	pr->flags.power_setup_done = 0;
	return 0;
}