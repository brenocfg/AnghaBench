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
 scalar_t__ POLARIS_DENSE_CONFIG_BASE ; 
 long ffz (unsigned long) ; 
 int /*<<< orphan*/  handle_irq (int) ; 
 int /*<<< orphan*/  isa_no_iack_sc_device_interrupt (unsigned long) ; 

__attribute__((used)) static void 
rx164_device_interrupt(unsigned long vector)
{
	unsigned long pld;
	volatile unsigned int *dirr;
	long i;

	/* Read the interrupt summary register.  On Polaris, this is
	   the DIRR register in PCI config space (offset 0x84).  */
	dirr = (void *)(POLARIS_DENSE_CONFIG_BASE + 0x84);
	pld = *dirr;

	/*
	 * Now for every possible bit set, work through them and call
	 * the appropriate interrupt handler.
	 */
	while (pld) {
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		if (i == 20) {
			isa_no_iack_sc_device_interrupt(vector);
		} else {
			handle_irq(16+i);
		}
	}
}