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
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_atlas_button_handler ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_dev ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int atlas_acpi_button_remove(struct acpi_device *device)
{
	acpi_status status;

	status = acpi_remove_address_space_handler(device->handle,
				0x81, &acpi_atlas_button_handler);
	if (ACPI_FAILURE(status))
		pr_err("error removing addr spc handler\n");

	input_unregister_device(input_dev);

	return 0;
}