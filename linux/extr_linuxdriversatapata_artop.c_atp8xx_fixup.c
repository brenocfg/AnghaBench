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
typedef  int u8 ;
struct pci_dev {int device; } ;

/* Variables and functions */
 int PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void atp8xx_fixup(struct pci_dev *pdev)
{
	if (pdev->device == 0x0005)
		/* BIOS may have left us in UDMA, clear it before libata probe */
		pci_write_config_byte(pdev, 0x54, 0);
	else if (pdev->device == 0x0008 || pdev->device == 0x0009) {
		u8 reg;

		/* Mac systems come up with some registers not set as we
		   will need them */

		/* Clear reset & test bits */
		pci_read_config_byte(pdev, 0x49, &reg);
		pci_write_config_byte(pdev, 0x49, reg & ~0x30);

		/* PCI latency must be > 0x80 for burst mode, tweak it
		 * if required.
		 */
		pci_read_config_byte(pdev, PCI_LATENCY_TIMER, &reg);
		if (reg <= 0x80)
			pci_write_config_byte(pdev, PCI_LATENCY_TIMER, 0x90);

		/* Enable IRQ output and burst mode */
		pci_read_config_byte(pdev, 0x4a, &reg);
		pci_write_config_byte(pdev, 0x4a, (reg & ~0x01) | 0x80);
	}
}