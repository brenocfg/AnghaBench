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
struct eeepc_laptop {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct eeepc_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  eeepc_backlight_exit (struct eeepc_laptop*) ; 
 int /*<<< orphan*/  eeepc_input_exit (struct eeepc_laptop*) ; 
 int /*<<< orphan*/  eeepc_led_exit (struct eeepc_laptop*) ; 
 int /*<<< orphan*/  eeepc_platform_exit (struct eeepc_laptop*) ; 
 int /*<<< orphan*/  eeepc_rfkill_exit (struct eeepc_laptop*) ; 
 int /*<<< orphan*/  kfree (struct eeepc_laptop*) ; 

__attribute__((used)) static int eeepc_acpi_remove(struct acpi_device *device)
{
	struct eeepc_laptop *eeepc = acpi_driver_data(device);

	eeepc_backlight_exit(eeepc);
	eeepc_rfkill_exit(eeepc);
	eeepc_input_exit(eeepc);
	eeepc_led_exit(eeepc);
	eeepc_platform_exit(eeepc);

	kfree(eeepc);
	return 0;
}