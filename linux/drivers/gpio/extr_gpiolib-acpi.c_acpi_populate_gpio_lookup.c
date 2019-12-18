#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  string_ptr; } ;
struct acpi_resource_gpio {scalar_t__ connection_type; int pin_table_length; int /*<<< orphan*/  triggering; int /*<<< orphan*/  polarity; int /*<<< orphan*/  pin_config; int /*<<< orphan*/ * pin_table; TYPE_2__ resource_source; } ;
struct TYPE_4__ {struct acpi_resource_gpio gpio; } ;
struct acpi_resource {scalar_t__ type; TYPE_1__ data; } ;
struct TYPE_6__ {int quirks; int gpioint; int /*<<< orphan*/  polarity; int /*<<< orphan*/  flags; int /*<<< orphan*/  triggering; int /*<<< orphan*/  pin_config; } ;
struct acpi_gpio_lookup {scalar_t__ index; int pin_index; int /*<<< orphan*/  active_low; TYPE_3__ info; int /*<<< orphan*/  desc; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int ACPI_GPIO_QUIRK_ONLY_GPIOIO ; 
 scalar_t__ ACPI_RESOURCE_GPIO_TYPE_INT ; 
 scalar_t__ ACPI_RESOURCE_TYPE_GPIO ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  acpi_get_gpiod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gpio_to_gpiod_flags (struct acpi_resource_gpio const*) ; 

__attribute__((used)) static int acpi_populate_gpio_lookup(struct acpi_resource *ares, void *data)
{
	struct acpi_gpio_lookup *lookup = data;

	if (ares->type != ACPI_RESOURCE_TYPE_GPIO)
		return 1;

	if (!lookup->desc) {
		const struct acpi_resource_gpio *agpio = &ares->data.gpio;
		bool gpioint = agpio->connection_type == ACPI_RESOURCE_GPIO_TYPE_INT;
		int pin_index;

		if (lookup->info.quirks & ACPI_GPIO_QUIRK_ONLY_GPIOIO && gpioint)
			lookup->index++;

		if (lookup->n++ != lookup->index)
			return 1;

		pin_index = lookup->pin_index;
		if (pin_index >= agpio->pin_table_length)
			return 1;

		lookup->desc = acpi_get_gpiod(agpio->resource_source.string_ptr,
					      agpio->pin_table[pin_index]);
		lookup->info.pin_config = agpio->pin_config;
		lookup->info.gpioint = gpioint;

		/*
		 * Polarity and triggering are only specified for GpioInt
		 * resource.
		 * Note: we expect here:
		 * - ACPI_ACTIVE_LOW == GPIO_ACTIVE_LOW
		 * - ACPI_ACTIVE_HIGH == GPIO_ACTIVE_HIGH
		 */
		if (lookup->info.gpioint) {
			lookup->info.flags = GPIOD_IN;
			lookup->info.polarity = agpio->polarity;
			lookup->info.triggering = agpio->triggering;
		} else {
			lookup->info.flags = acpi_gpio_to_gpiod_flags(agpio);
			lookup->info.polarity = lookup->active_low;
		}
	}

	return 1;
}