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
typedef  unsigned long* vulp ;

/* Variables and functions */
 scalar_t__ PYXIS_INT_REQ ; 
 unsigned long cached_irq_mask ; 
 unsigned int ffz (unsigned long) ; 
 int /*<<< orphan*/  handle_irq (int) ; 
 int /*<<< orphan*/  isa_device_interrupt (unsigned long) ; 

void 
pyxis_device_interrupt(unsigned long vector)
{
	unsigned long pld;
	unsigned int i;

	/* Read the interrupt summary register of PYXIS */
	pld = *(vulp)PYXIS_INT_REQ;
	pld &= cached_irq_mask;

	/*
	 * Now for every possible bit set, work through them and call
	 * the appropriate interrupt handler.
	 */
	while (pld) {
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		if (i == 7)
			isa_device_interrupt(vector);
		else
			handle_irq(16+i);
	}
}