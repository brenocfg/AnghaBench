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
struct pci_dev {int dummy; } ;
struct ata_port {size_t port_no; TYPE_1__* host; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ata_sff_prereset (struct ata_link*,unsigned long) ; 
 int /*<<< orphan*/  pci_test_config_bits (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * piix_enable_bits ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int piix_pata_prereset(struct ata_link *link, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &piix_enable_bits[ap->port_no]))
		return -ENOENT;
	return ata_sff_prereset(link, deadline);
}