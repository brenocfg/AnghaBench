#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int irq; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int via_vlink_dev_hi ; 
 int via_vlink_dev_lo ; 

__attribute__((used)) static void quirk_via_vlink(struct pci_dev *dev)
{
	u8 irq, new_irq;

	/* Check if we have VLink at all */
	if (via_vlink_dev_lo == -1)
		return;

	new_irq = dev->irq;

	/* Don't quirk interrupts outside the legacy IRQ range */
	if (!new_irq || new_irq > 15)
		return;

	/* Internal device ? */
	if (dev->bus->number != 0 || PCI_SLOT(dev->devfn) > via_vlink_dev_hi ||
	    PCI_SLOT(dev->devfn) < via_vlink_dev_lo)
		return;

	/*
	 * This is an internal VLink device on a PIC interrupt. The BIOS
	 * ought to have set this but may not have, so we redo it.
	 */
	pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &irq);
	if (new_irq != irq) {
		pci_info(dev, "VIA VLink IRQ fixup, from %d to %d\n",
			irq, new_irq);
		udelay(15);	/* unknown if delay really needed */
		pci_write_config_byte(dev, PCI_INTERRUPT_LINE, new_irq);
	}
}