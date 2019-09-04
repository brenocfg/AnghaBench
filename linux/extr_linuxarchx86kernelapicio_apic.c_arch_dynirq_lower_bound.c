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

/* Variables and functions */
 unsigned int gsi_top ; 
 unsigned int ioapic_dynirq_base ; 
 scalar_t__ ioapic_initialized ; 

unsigned int arch_dynirq_lower_bound(unsigned int from)
{
	/*
	 * dmar_alloc_hwirq() may be called before setup_IO_APIC(), so use
	 * gsi_top if ioapic_dynirq_base hasn't been initialized yet.
	 */
	return ioapic_initialized ? ioapic_dynirq_base : gsi_top;
}