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
struct pci_dev {int dummy; } ;
struct mic_device {struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  mic_to_dma_addr (struct mic_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_unmap (struct mic_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void
mic_unmap_single(struct mic_device *mdev, dma_addr_t mic_addr, size_t size)
{
	struct pci_dev *pdev = mdev->pdev;
	dma_addr_t dma_addr = mic_to_dma_addr(mdev, mic_addr);
	mic_unmap(mdev, mic_addr, size);
	pci_unmap_single(pdev, dma_addr, size, PCI_DMA_BIDIRECTIONAL);
}