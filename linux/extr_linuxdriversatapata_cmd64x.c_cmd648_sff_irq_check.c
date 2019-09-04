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
 int MRDMODE_INTR_CH0 ; 
 int MRDMODE_INTR_CH1 ; 
 int inb (unsigned long) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cmd648_sff_irq_check(struct ata_port *ap)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned long base = pci_resource_start(pdev, 4);
	int irq_mask = ap->port_no ? MRDMODE_INTR_CH1 : MRDMODE_INTR_CH0;
	u8 mrdmode = inb(base + 1);

	return mrdmode & irq_mask;
}