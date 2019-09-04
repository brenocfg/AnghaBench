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
 unsigned int PCI_CLK_33 ; 
 unsigned int PCI_CLK_33A ; 
 unsigned char SC1200_REV_B1 ; 
 unsigned char inb (int) ; 
 unsigned int inw (int) ; 

__attribute__((used)) static unsigned short sc1200_get_pci_clock (void)
{
	unsigned char chip_id, silicon_revision;
	unsigned int pci_clock;
	/*
	 * Check the silicon revision, as not all versions of the chip
	 * have the register with the fast PCI bus timings.
	 */
	chip_id = inb (0x903c);
	silicon_revision = inb (0x903d);

	// Read the fast pci clock frequency
	if (chip_id == 0x04 && silicon_revision < SC1200_REV_B1) {
		pci_clock = PCI_CLK_33;
	} else {
		// check clock generator configuration (cfcc)
		// the clock is in bits 8 and 9 of this word

		pci_clock = inw (0x901e);
		pci_clock >>= 8;
		pci_clock &= 0x03;
		if (pci_clock == PCI_CLK_33A)
			pci_clock = PCI_CLK_33;
	}
	return pci_clock;
}