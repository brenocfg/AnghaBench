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
typedef  int u32 ;
struct pcilynx {int /*<<< orphan*/  rcv_start_pcl_bus; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int LINK_INT_PHY_BUSRESET ; 
 int /*<<< orphan*/  LINK_INT_STATUS ; 
 int PCI_INT_DMA0_HLT ; 
 int PCI_INT_INT_PEND ; 
 int PCI_INT_P1394_INT ; 
 int /*<<< orphan*/  PCI_INT_STATUS ; 
 int /*<<< orphan*/  bus_reset_irq_handler (struct pcilynx*) ; 
 int /*<<< orphan*/  packet_irq_handler (struct pcilynx*) ; 
 int reg_read (struct pcilynx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct pcilynx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_pcl (struct pcilynx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
irq_handler(int irq, void *device)
{
	struct pcilynx *lynx = device;
	u32 pci_int_status;

	pci_int_status = reg_read(lynx, PCI_INT_STATUS);

	if (pci_int_status == ~0)
		/* Card was ejected. */
		return IRQ_NONE;

	if ((pci_int_status & PCI_INT_INT_PEND) == 0)
		/* Not our interrupt, bail out quickly. */
		return IRQ_NONE;

	if ((pci_int_status & PCI_INT_P1394_INT) != 0) {
		u32 link_int_status;

		link_int_status = reg_read(lynx, LINK_INT_STATUS);
		reg_write(lynx, LINK_INT_STATUS, link_int_status);

		if ((link_int_status & LINK_INT_PHY_BUSRESET) > 0)
			bus_reset_irq_handler(lynx);
	}

	/* Clear the PCI_INT_STATUS register only after clearing the
	 * LINK_INT_STATUS register; otherwise the PCI_INT_P1394 will
	 * be set again immediately. */

	reg_write(lynx, PCI_INT_STATUS, pci_int_status);

	if ((pci_int_status & PCI_INT_DMA0_HLT) > 0) {
		packet_irq_handler(lynx);
		run_pcl(lynx, lynx->rcv_start_pcl_bus, 0);
	}

	return IRQ_HANDLED;
}