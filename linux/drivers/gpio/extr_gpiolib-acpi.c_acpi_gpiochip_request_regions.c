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
struct acpi_gpio_chip {int /*<<< orphan*/  conn_lock; int /*<<< orphan*/  conns; struct gpio_chip* chip; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_GPIO ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_gpio_adr_space_handler ; 
 int /*<<< orphan*/  acpi_install_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_gpio_chip*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_gpiochip_request_regions(struct acpi_gpio_chip *achip)
{
	struct gpio_chip *chip = achip->chip;
	acpi_handle handle = ACPI_HANDLE(chip->parent);
	acpi_status status;

	INIT_LIST_HEAD(&achip->conns);
	mutex_init(&achip->conn_lock);
	status = acpi_install_address_space_handler(handle, ACPI_ADR_SPACE_GPIO,
						    acpi_gpio_adr_space_handler,
						    NULL, achip);
	if (ACPI_FAILURE(status))
		dev_err(chip->parent,
		        "Failed to install GPIO OpRegion handler\n");
}