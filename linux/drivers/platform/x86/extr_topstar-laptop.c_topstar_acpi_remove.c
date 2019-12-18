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
struct topstar_laptop {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct topstar_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  kfree (struct topstar_laptop*) ; 
 scalar_t__ led_workaround ; 
 int /*<<< orphan*/  topstar_acpi_exit (struct topstar_laptop*) ; 
 int /*<<< orphan*/  topstar_input_exit (struct topstar_laptop*) ; 
 int /*<<< orphan*/  topstar_led_exit (struct topstar_laptop*) ; 
 int /*<<< orphan*/  topstar_platform_exit (struct topstar_laptop*) ; 

__attribute__((used)) static int topstar_acpi_remove(struct acpi_device *device)
{
	struct topstar_laptop *topstar = acpi_driver_data(device);

	if (led_workaround)
		topstar_led_exit(topstar);

	topstar_input_exit(topstar);
	topstar_platform_exit(topstar);
	topstar_acpi_exit(topstar);

	kfree(topstar);
	return 0;
}