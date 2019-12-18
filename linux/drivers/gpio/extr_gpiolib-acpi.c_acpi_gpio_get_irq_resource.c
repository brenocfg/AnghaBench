#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_resource_gpio {scalar_t__ connection_type; } ;
struct TYPE_2__ {struct acpi_resource_gpio gpio; } ;
struct acpi_resource {scalar_t__ type; TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_GPIO_TYPE_INT ; 
 scalar_t__ ACPI_RESOURCE_TYPE_GPIO ; 

bool acpi_gpio_get_irq_resource(struct acpi_resource *ares,
				struct acpi_resource_gpio **agpio)
{
	struct acpi_resource_gpio *gpio;

	if (ares->type != ACPI_RESOURCE_TYPE_GPIO)
		return false;

	gpio = &ares->data.gpio;
	if (gpio->connection_type != ACPI_RESOURCE_GPIO_TYPE_INT)
		return false;

	*agpio = gpio;
	return true;
}