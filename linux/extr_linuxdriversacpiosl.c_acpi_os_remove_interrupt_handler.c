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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_osd_handler ;
struct TYPE_2__ {scalar_t__ sci_interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  INVALID_ACPI_IRQ ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_irq ; 
 int /*<<< orphan*/ * acpi_irq_handler ; 
 int /*<<< orphan*/  acpi_sci_irq ; 
 int /*<<< orphan*/  acpi_sci_irq_valid () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

acpi_status acpi_os_remove_interrupt_handler(u32 gsi, acpi_osd_handler handler)
{
	if (gsi != acpi_gbl_FADT.sci_interrupt || !acpi_sci_irq_valid())
		return AE_BAD_PARAMETER;

	free_irq(acpi_sci_irq, acpi_irq);
	acpi_irq_handler = NULL;
	acpi_sci_irq = INVALID_ACPI_IRQ;

	return AE_OK;
}