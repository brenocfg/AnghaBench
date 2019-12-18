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
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_selected_regions (struct pci_dev*,int) ; 
 scalar_t__ pci_request_selected_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_try_set_mwi (struct pci_dev*) ; 

__attribute__((used)) static int
csio_pci_init(struct pci_dev *pdev, int *bars)
{
	int rv = -ENODEV;

	*bars = pci_select_bars(pdev, IORESOURCE_MEM);

	if (pci_enable_device_mem(pdev))
		goto err;

	if (pci_request_selected_regions(pdev, *bars, KBUILD_MODNAME))
		goto err_disable_device;

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	rv = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (rv)
		rv = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (rv) {
		rv = -ENODEV;
		dev_err(&pdev->dev, "No suitable DMA available.\n");
		goto err_release_regions;
	}

	return 0;

err_release_regions:
	pci_release_selected_regions(pdev, *bars);
err_disable_device:
	pci_disable_device(pdev);
err:
	return rv;

}