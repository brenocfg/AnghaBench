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
struct pci_dev {int dummy; } ;
struct ata_port {scalar_t__ port_no; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int inb (unsigned long) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pdc202xx_irq_check(struct ata_port *ap)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	unsigned long master	= pci_resource_start(pdev, 4);
	u8 sc1d			= inb(master + 0x1d);

	if (ap->port_no) {
		/*
		 * bit 7: error, bit 6: interrupting,
		 * bit 5: FIFO full, bit 4: FIFO empty
		 */
		return sc1d & 0x40;
	} else	{
		/*
		 * bit 3: error, bit 2: interrupting,
		 * bit 1: FIFO full, bit 0: FIFO empty
		 */
		return sc1d & 0x04;
	}
}