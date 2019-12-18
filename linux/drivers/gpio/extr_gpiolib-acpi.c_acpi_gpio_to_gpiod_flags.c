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
struct acpi_resource_gpio {int io_restriction; int /*<<< orphan*/  pin_config; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
#define  ACPI_IO_RESTRICT_INPUT 131 
#define  ACPI_IO_RESTRICT_OUTPUT 130 
#define  ACPI_PIN_CONFIG_PULLDOWN 129 
#define  ACPI_PIN_CONFIG_PULLUP 128 
 int GPIOD_ASIS ; 
 int GPIOD_IN ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 

__attribute__((used)) static enum gpiod_flags
acpi_gpio_to_gpiod_flags(const struct acpi_resource_gpio *agpio)
{
	switch (agpio->io_restriction) {
	case ACPI_IO_RESTRICT_INPUT:
		return GPIOD_IN;
	case ACPI_IO_RESTRICT_OUTPUT:
		/*
		 * ACPI GPIO resources don't contain an initial value for the
		 * GPIO. Therefore we deduce that value from the pull field
		 * instead. If the pin is pulled up we assume default to be
		 * high, if it is pulled down we assume default to be low,
		 * otherwise we leave pin untouched.
		 */
		switch (agpio->pin_config) {
		case ACPI_PIN_CONFIG_PULLUP:
			return GPIOD_OUT_HIGH;
		case ACPI_PIN_CONFIG_PULLDOWN:
			return GPIOD_OUT_LOW;
		default:
			break;
		}
	default:
		break;
	}

	/*
	 * Assume that the BIOS has configured the direction and pull
	 * accordingly.
	 */
	return GPIOD_ASIS;
}