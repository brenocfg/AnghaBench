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
 int inw (int) ; 
 int /*<<< orphan*/  isa_device_interrupt (unsigned long) ; 

__attribute__((used)) static void
takara_device_interrupt(unsigned long vector)
{
	unsigned intstatus;

	/*
	 * The PALcode will have passed us vectors 0x800 or 0x810,
	 * which are fairly arbitrary values and serve only to tell
	 * us whether an interrupt has come in on IRQ0 or IRQ1. If
	 * it's IRQ1 it's a PCI interrupt; if it's IRQ0, it's
	 * probably ISA, but PCI interrupts can come through IRQ0
	 * as well if the interrupt controller isn't in accelerated
	 * mode.
	 *
	 * OTOH, the accelerator thing doesn't seem to be working
	 * overly well, so what we'll do instead is try directly
	 * examining the Master Interrupt Register to see if it's a
	 * PCI interrupt, and if _not_ then we'll pass it on to the
	 * ISA handler.
	 */

	intstatus = inw(0x500) & 15;
	if (intstatus) {
		/*
		 * This is a PCI interrupt. Check each bit and
		 * despatch an interrupt if it's set.
		 */

		if (intstatus & 8) handle_irq(16+3);
		if (intstatus & 4) handle_irq(16+2);
		if (intstatus & 2) handle_irq(16+1);
		if (intstatus & 1) handle_irq(16+0);
	} else {
		isa_device_interrupt (vector);
	}
}