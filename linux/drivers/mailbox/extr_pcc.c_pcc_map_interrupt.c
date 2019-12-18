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
 int ACPI_ACTIVE_HIGH ; 
 int ACPI_ACTIVE_LOW ; 
 int ACPI_EDGE_SENSITIVE ; 
 int ACPI_LEVEL_SENSITIVE ; 
 int ACPI_PCCT_INTERRUPT_MODE ; 
 int ACPI_PCCT_INTERRUPT_POLARITY ; 
 int acpi_register_gsi (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int pcc_map_interrupt(u32 interrupt, u32 flags)
{
	int trigger, polarity;

	if (!interrupt)
		return 0;

	trigger = (flags & ACPI_PCCT_INTERRUPT_MODE) ? ACPI_EDGE_SENSITIVE
			: ACPI_LEVEL_SENSITIVE;

	polarity = (flags & ACPI_PCCT_INTERRUPT_POLARITY) ? ACPI_ACTIVE_LOW
			: ACPI_ACTIVE_HIGH;

	return acpi_register_gsi(NULL, interrupt, trigger, polarity);
}