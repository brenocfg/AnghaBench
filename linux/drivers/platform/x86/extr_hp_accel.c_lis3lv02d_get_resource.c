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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_resource_extended_irq {int /*<<< orphan*/ * interrupts; } ;
struct TYPE_2__ {struct acpi_resource_extended_irq extended_irq; } ;
struct acpi_resource {scalar_t__ type; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_TYPE_EXTENDED_IRQ ; 
 int /*<<< orphan*/  AE_OK ; 

__attribute__((used)) static acpi_status
lis3lv02d_get_resource(struct acpi_resource *resource, void *context)
{
	if (resource->type == ACPI_RESOURCE_TYPE_EXTENDED_IRQ) {
		struct acpi_resource_extended_irq *irq;
		u32 *device_irq = context;

		irq = &resource->data.extended_irq;
		*device_irq = irq->interrupts[0];
	}

	return AE_OK;
}