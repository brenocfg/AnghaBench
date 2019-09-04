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
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct acpi_gpio_chip {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_detach_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  acpi_gpio_chip_dh ; 
 int /*<<< orphan*/  acpi_gpiochip_free_regions (struct acpi_gpio_chip*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct acpi_gpio_chip*) ; 

void acpi_gpiochip_remove(struct gpio_chip *chip)
{
	struct acpi_gpio_chip *acpi_gpio;
	acpi_handle handle;
	acpi_status status;

	if (!chip || !chip->parent)
		return;

	handle = ACPI_HANDLE(chip->parent);
	if (!handle)
		return;

	status = acpi_get_data(handle, acpi_gpio_chip_dh, (void **)&acpi_gpio);
	if (ACPI_FAILURE(status)) {
		dev_warn(chip->parent, "Failed to retrieve ACPI GPIO chip\n");
		return;
	}

	acpi_gpiochip_free_regions(acpi_gpio);

	acpi_detach_data(handle, acpi_gpio_chip_dh);
	kfree(acpi_gpio);
}