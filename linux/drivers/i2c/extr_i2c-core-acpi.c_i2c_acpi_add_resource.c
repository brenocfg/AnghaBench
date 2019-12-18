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
struct resource {int dummy; } ;
struct acpi_resource {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_dev_resource_interrupt (struct acpi_resource*,int /*<<< orphan*/ ,struct resource*) ; 
 int i2c_dev_irq_from_resources (struct resource*,int) ; 

__attribute__((used)) static int i2c_acpi_add_resource(struct acpi_resource *ares, void *data)
{
	int *irq = data;
	struct resource r;

	if (*irq <= 0 && acpi_dev_resource_interrupt(ares, 0, &r))
		*irq = i2c_dev_irq_from_resources(&r, 1);

	return 1; /* No need to add resource to the list */
}