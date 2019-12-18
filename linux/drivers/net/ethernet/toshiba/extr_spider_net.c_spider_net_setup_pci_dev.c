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
struct spider_net_card {int /*<<< orphan*/  regs; TYPE_1__* netdev; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned long mem_start; unsigned long mem_end; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ioremap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 struct spider_net_card* spider_net_alloc_card () ; 
 int /*<<< orphan*/  spider_net_driver_name ; 

__attribute__((used)) static struct spider_net_card *
spider_net_setup_pci_dev(struct pci_dev *pdev)
{
	struct spider_net_card *card;
	unsigned long mmio_start, mmio_len;

	if (pci_enable_device(pdev)) {
		dev_err(&pdev->dev, "Couldn't enable PCI device\n");
		return NULL;
	}

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev,
		        "Couldn't find proper PCI device base address.\n");
		goto out_disable_dev;
	}

	if (pci_request_regions(pdev, spider_net_driver_name)) {
		dev_err(&pdev->dev,
		        "Couldn't obtain PCI resources, aborting.\n");
		goto out_disable_dev;
	}

	pci_set_master(pdev);

	card = spider_net_alloc_card();
	if (!card) {
		dev_err(&pdev->dev,
		        "Couldn't allocate net_device structure, aborting.\n");
		goto out_release_regions;
	}
	card->pdev = pdev;

	/* fetch base address and length of first resource */
	mmio_start = pci_resource_start(pdev, 0);
	mmio_len = pci_resource_len(pdev, 0);

	card->netdev->mem_start = mmio_start;
	card->netdev->mem_end = mmio_start + mmio_len;
	card->regs = ioremap(mmio_start, mmio_len);

	if (!card->regs) {
		dev_err(&pdev->dev,
		        "Couldn't obtain PCI resources, aborting.\n");
		goto out_release_regions;
	}

	return card;

out_release_regions:
	pci_release_regions(pdev);
out_disable_dev:
	pci_disable_device(pdev);
	return NULL;
}