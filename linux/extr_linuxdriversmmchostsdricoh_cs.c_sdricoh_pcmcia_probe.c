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
struct pcmcia_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * prod_id; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_RICOH_RL5C476 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_RICOH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  sdricoh_init_mmc (struct pci_dev*,struct pcmcia_device*) ; 

__attribute__((used)) static int sdricoh_pcmcia_probe(struct pcmcia_device *pcmcia_dev)
{
	struct pci_dev *pci_dev = NULL;

	dev_info(&pcmcia_dev->dev, "Searching MMC controller for pcmcia device"
		" %s %s ...\n", pcmcia_dev->prod_id[0], pcmcia_dev->prod_id[1]);

	/* search pci cardbus bridge that contains the mmc controller */
	/* the io region is already claimed by yenta_socket... */
	while ((pci_dev =
		pci_get_device(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C476,
			       pci_dev))) {
		/* try to init the device */
		if (!sdricoh_init_mmc(pci_dev, pcmcia_dev)) {
			dev_info(&pcmcia_dev->dev, "MMC controller found\n");
			return 0;
		}

	}
	dev_err(&pcmcia_dev->dev, "No MMC controller was found.\n");
	return -ENODEV;
}