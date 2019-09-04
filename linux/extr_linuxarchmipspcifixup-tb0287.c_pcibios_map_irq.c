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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {unsigned char number; } ;

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int TB0287_PCI_SLOT_IRQ ; 
 int TB0287_RTL8110_IRQ ; 
 int TB0287_SIL680A_IRQ ; 
 int TB0287_SM501_IRQ ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	unsigned char bus;
	int irq = -1;

	bus = dev->bus->number;
	if (bus == 0) {
		switch (slot) {
		case 16:
			irq = TB0287_SM501_IRQ;
			break;
		case 17:
			irq = TB0287_SIL680A_IRQ;
			break;
		default:
			break;
		}
	} else if (bus == 1) {
		switch (PCI_SLOT(dev->devfn)) {
		case 0:
			irq = TB0287_PCI_SLOT_IRQ;
			break;
		case 2:
		case 3:
			irq = TB0287_RTL8110_IRQ;
			break;
		default:
			break;
		}
	} else if (bus > 1) {
		irq = TB0287_PCI_SLOT_IRQ;
	}

	return irq;
}