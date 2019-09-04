#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pin_table_length; } ;
struct TYPE_4__ {TYPE_1__ gpio; } ;
struct acpi_resource {scalar_t__ type; TYPE_2__ data; } ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_TYPE_GPIO ; 

__attribute__((used)) static int acpi_find_gpio_count(struct acpi_resource *ares, void *data)
{
	unsigned int *count = data;

	if (ares->type == ACPI_RESOURCE_TYPE_GPIO)
		*count += ares->data.gpio.pin_table_length;

	return 1;
}