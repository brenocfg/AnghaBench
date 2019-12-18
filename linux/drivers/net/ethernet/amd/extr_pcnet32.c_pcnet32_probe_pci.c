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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int NETIF_MSG_PROBE ; 
 int /*<<< orphan*/  PCNET32_DMA_MASK ; 
 int /*<<< orphan*/  PCNET32_TOTAL_SIZE ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcnet32_debug ; 
 int pcnet32_probe1 (unsigned long,int,struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcnet32_probe_pci(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	unsigned long ioaddr;
	int err;

	err = pci_enable_device(pdev);
	if (err < 0) {
		if (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("failed to enable device -- err=%d\n", err);
		return err;
	}
	pci_set_master(pdev);

	ioaddr = pci_resource_start(pdev, 0);
	if (!ioaddr) {
		if (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("card has no PCI IO resources, aborting\n");
		err = -ENODEV;
		goto err_disable_dev;
	}

	err = pci_set_dma_mask(pdev, PCNET32_DMA_MASK);
	if (err) {
		if (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("architecture does not support 32bit PCI busmaster DMA\n");
		goto err_disable_dev;
	}
	if (!request_region(ioaddr, PCNET32_TOTAL_SIZE, "pcnet32_probe_pci")) {
		if (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("io address range already allocated\n");
		err = -EBUSY;
		goto err_disable_dev;
	}

	err = pcnet32_probe1(ioaddr, 1, pdev);

err_disable_dev:
	if (err < 0)
		pci_disable_device(pdev);

	return err;
}