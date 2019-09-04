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
 unsigned int ffz (unsigned long) ; 
 int /*<<< orphan*/  handle_irq (unsigned int) ; 
 unsigned long inb (int) ; 
 scalar_t__ inw (int) ; 
 int /*<<< orphan*/  isa_device_interrupt (unsigned long) ; 

__attribute__((used)) static void 
noritake_device_interrupt(unsigned long vector)
{
	unsigned long pld;
	unsigned int i;

	/* Read the interrupt summary registers of NORITAKE */
	pld = (((unsigned long) inw(0x54c) << 32)
	       | ((unsigned long) inw(0x54a) << 16)
	       | ((unsigned long) inb(0xa0) << 8)
	       | inb(0x20));

	/*
	 * Now for every possible bit set, work through them and call
	 * the appropriate interrupt handler.
	 */
	while (pld) {
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		if (i < 16) {
			isa_device_interrupt(vector);
		} else {
			handle_irq(i);
		}
	}
}