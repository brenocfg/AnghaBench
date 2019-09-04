#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octeon_device {TYPE_1__* pci_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 scalar_t__ pci_enable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_1__*) ; 

__attribute__((used)) static int octeon_pci_os_setup(struct octeon_device *oct)
{
	/* setup PCI stuff first */
	if (pci_enable_device(oct->pci_dev)) {
		dev_err(&oct->pci_dev->dev, "pci_enable_device failed\n");
		return 1;
	}

	if (dma_set_mask_and_coherent(&oct->pci_dev->dev, DMA_BIT_MASK(64))) {
		dev_err(&oct->pci_dev->dev, "Unexpected DMA device capability\n");
		pci_disable_device(oct->pci_dev);
		return 1;
	}

	/* Enable PCI DMA Master. */
	pci_set_master(oct->pci_dev);

	return 0;
}