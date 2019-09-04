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
struct gpio_chip {int /*<<< orphan*/  parent; int /*<<< orphan*/  names; } ;
struct acpi_gpio_chip {int /*<<< orphan*/  deferred_req_irqs_list_entry; int /*<<< orphan*/  events; struct gpio_chip* chip; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_attach_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_gpio_chip*) ; 
 int /*<<< orphan*/  acpi_gpio_chip_dh ; 
 int /*<<< orphan*/  acpi_gpiochip_request_regions (struct acpi_gpio_chip*) ; 
 int /*<<< orphan*/  acpi_gpiochip_scan_gpios (struct acpi_gpio_chip*) ; 
 int /*<<< orphan*/  acpi_walk_dep_device_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devprop_gpiochip_set_names (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_gpio_chip*) ; 
 struct acpi_gpio_chip* kzalloc (int,int /*<<< orphan*/ ) ; 

void acpi_gpiochip_add(struct gpio_chip *chip)
{
	struct acpi_gpio_chip *acpi_gpio;
	acpi_handle handle;
	acpi_status status;

	if (!chip || !chip->parent)
		return;

	handle = ACPI_HANDLE(chip->parent);
	if (!handle)
		return;

	acpi_gpio = kzalloc(sizeof(*acpi_gpio), GFP_KERNEL);
	if (!acpi_gpio) {
		dev_err(chip->parent,
			"Failed to allocate memory for ACPI GPIO chip\n");
		return;
	}

	acpi_gpio->chip = chip;
	INIT_LIST_HEAD(&acpi_gpio->events);
	INIT_LIST_HEAD(&acpi_gpio->deferred_req_irqs_list_entry);

	status = acpi_attach_data(handle, acpi_gpio_chip_dh, acpi_gpio);
	if (ACPI_FAILURE(status)) {
		dev_err(chip->parent, "Failed to attach ACPI GPIO chip\n");
		kfree(acpi_gpio);
		return;
	}

	if (!chip->names)
		devprop_gpiochip_set_names(chip, dev_fwnode(chip->parent));

	acpi_gpiochip_request_regions(acpi_gpio);
	acpi_gpiochip_scan_gpios(acpi_gpio);
	acpi_walk_dep_device_list(handle);
}