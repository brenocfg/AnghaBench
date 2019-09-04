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
 int /*<<< orphan*/  handle_irq (int) ; 

__attribute__((used)) static void 
noritake_srm_device_interrupt(unsigned long vector)
{
	int irq;

	irq = (vector - 0x800) >> 4;

	/*
	 * I really hate to do this, too, but the NORITAKE SRM console also
	 * reports PCI vectors *lower* than I expected from the bit numbers
	 * in the documentation.
	 * But I really don't want to change the fixup code for allocation
	 * of IRQs, nor the alpha_irq_mask maintenance stuff, both of which
	 * look nice and clean now.
	 * So, here's this additional grotty hack... :-(
	 */
	if (irq >= 16)
		irq = irq + 1;

	handle_irq(irq);
}