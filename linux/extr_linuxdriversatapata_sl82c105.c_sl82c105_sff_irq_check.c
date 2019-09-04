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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct ata_port {scalar_t__ port_no; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTRL_IDE_IRQA ; 
 int CTRL_IDE_IRQB ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sl82c105_sff_irq_check(struct ata_port *ap)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u32 val, mask		= ap->port_no ? CTRL_IDE_IRQB : CTRL_IDE_IRQA;

	pci_read_config_dword(pdev, 0x40, &val);

	return val & mask;
}