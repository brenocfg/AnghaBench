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
struct pci_dev {int device; } ;
struct ata_port {scalar_t__ port_no; TYPE_1__* host; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ata_sff_prereset (struct ata_link*,unsigned long) ; 
 int /*<<< orphan*/  marvell_pata_active (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_pre_reset(struct ata_link *link, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (pdev->device == 0x6145 && ap->port_no == 0 &&
		!marvell_pata_active(pdev))	/* PATA enable ? */
			return -ENOENT;

	return ata_sff_prereset(link, deadline);
}