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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int beiscsi_enable_pci(struct pci_dev *pcidev)
{
	int ret;

	ret = pci_enable_device(pcidev);
	if (ret) {
		dev_err(&pcidev->dev,
			"beiscsi_enable_pci - enable device failed\n");
		return ret;
	}

	ret = pci_request_regions(pcidev, DRV_NAME);
	if (ret) {
		dev_err(&pcidev->dev,
				"beiscsi_enable_pci - request region failed\n");
		goto pci_dev_disable;
	}

	pci_set_master(pcidev);
	ret = dma_set_mask_and_coherent(&pcidev->dev, DMA_BIT_MASK(64));
	if (ret) {
		ret = dma_set_mask_and_coherent(&pcidev->dev, DMA_BIT_MASK(32));
		if (ret) {
			dev_err(&pcidev->dev, "Could not set PCI DMA Mask\n");
			goto pci_region_release;
		}
	}
	return 0;

pci_region_release:
	pci_release_regions(pcidev);
pci_dev_disable:
	pci_disable_device(pcidev);

	return ret;
}