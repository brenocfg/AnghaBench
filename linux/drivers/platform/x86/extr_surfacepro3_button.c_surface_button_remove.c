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
struct surface_button {int /*<<< orphan*/  input; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct surface_button* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct surface_button*) ; 

__attribute__((used)) static int surface_button_remove(struct acpi_device *device)
{
	struct surface_button *button = acpi_driver_data(device);

	input_unregister_device(button->input);
	kfree(button);
	return 0;
}