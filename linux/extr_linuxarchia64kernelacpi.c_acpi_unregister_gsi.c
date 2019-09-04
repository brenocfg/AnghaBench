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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ ACPI_IRQ_MODEL_PLATFORM ; 
 scalar_t__ acpi_irq_model ; 
 scalar_t__ has_8259 ; 
 int /*<<< orphan*/  iosapic_unregister_intr (int) ; 

void acpi_unregister_gsi(u32 gsi)
{
	if (acpi_irq_model == ACPI_IRQ_MODEL_PLATFORM)
		return;

	if (has_8259 && gsi < 16)
		return;

	iosapic_unregister_intr(gsi);
}