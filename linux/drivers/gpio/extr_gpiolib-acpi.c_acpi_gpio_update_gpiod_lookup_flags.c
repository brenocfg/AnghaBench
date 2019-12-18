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
struct acpi_gpio_info {int pin_config; unsigned long polarity; } ;

/* Variables and functions */
#define  ACPI_PIN_CONFIG_PULLDOWN 129 
#define  ACPI_PIN_CONFIG_PULLUP 128 
 unsigned long GPIO_ACTIVE_LOW ; 
 unsigned long GPIO_PULL_DOWN ; 
 unsigned long GPIO_PULL_UP ; 

int acpi_gpio_update_gpiod_lookup_flags(unsigned long *lookupflags,
					struct acpi_gpio_info *info)
{
	switch (info->pin_config) {
	case ACPI_PIN_CONFIG_PULLUP:
		*lookupflags |= GPIO_PULL_UP;
		break;
	case ACPI_PIN_CONFIG_PULLDOWN:
		*lookupflags |= GPIO_PULL_DOWN;
		break;
	default:
		break;
	}

	if (info->polarity == GPIO_ACTIVE_LOW)
		*lookupflags |= GPIO_ACTIVE_LOW;

	return 0;
}