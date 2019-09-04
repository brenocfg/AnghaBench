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
struct mic_device {struct pci_dev* pdev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,size_t) ; 
 scalar_t__ mic_map (struct mic_device*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  pci_dma_mapping_error (struct pci_dev*,scalar_t__) ; 
 scalar_t__ pci_map_single (struct pci_dev*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 

dma_addr_t mic_map_single(struct mic_device *mdev, void *va, size_t size)
{
	dma_addr_t mic_addr = 0;
	struct pci_dev *pdev = mdev->pdev;
	dma_addr_t dma_addr =
		pci_map_single(pdev, va, size, PCI_DMA_BIDIRECTIONAL);

	if (!pci_dma_mapping_error(pdev, dma_addr)) {
		mic_addr = mic_map(mdev, dma_addr, size);
		if (!mic_addr) {
			dev_err(&mdev->pdev->dev,
				"mic_map failed dma_addr 0x%llx size 0x%lx\n",
				dma_addr, size);
			pci_unmap_single(pdev, dma_addr,
					 size, PCI_DMA_BIDIRECTIONAL);
		}
	}
	return mic_addr;
}