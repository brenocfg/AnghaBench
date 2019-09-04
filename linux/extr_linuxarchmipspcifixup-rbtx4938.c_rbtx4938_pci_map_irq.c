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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int RBTX4938_IRQ_IOC_PCIA ; 
 int RBTX4938_IRQ_IOC_PCIB ; 
 int RBTX4938_IRQ_IOC_PCIC ; 
 int RBTX4938_IRQ_IOC_PCID ; 
 int TX4927_PCIC_IDSEL_AD_TO_SLOT (int) ; 
 int TXX9_PCI_OPT_PICMG ; 
 int tx4938_pcic1_map_irq (struct pci_dev const*,int) ; 
 int txx9_pci_option ; 

int rbtx4938_pci_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	int irq = tx4938_pcic1_map_irq(dev, slot);

	if (irq >= 0)
		return irq;
	irq = pin;
	/* IRQ rotation */
	irq--;	/* 0-3 */
	if (slot == TX4927_PCIC_IDSEL_AD_TO_SLOT(23)) {
		/* PCI CardSlot (IDSEL=A23) */
		/* PCIA => PCIA (IDSEL=A23) */
		irq = (irq + 0 + slot) % 4;
	} else {
		/* PCI Backplane */
		if (txx9_pci_option & TXX9_PCI_OPT_PICMG)
			irq = (irq + 33 - slot) % 4;
		else
			irq = (irq + 3 + slot) % 4;
	}
	irq++;	/* 1-4 */

	switch (irq) {
	case 1:
		irq = RBTX4938_IRQ_IOC_PCIA;
		break;
	case 2:
		irq = RBTX4938_IRQ_IOC_PCIB;
		break;
	case 3:
		irq = RBTX4938_IRQ_IOC_PCIC;
		break;
	case 4:
		irq = RBTX4938_IRQ_IOC_PCID;
		break;
	}
	return irq;
}