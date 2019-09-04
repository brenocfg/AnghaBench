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
struct bnad {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_NAME ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int
bnad_pci_init(struct bnad *bnad,
	      struct pci_dev *pdev, bool *using_dac)
{
	int err;

	err = pci_enable_device(pdev);
	if (err)
		return err;
	err = pci_request_regions(pdev, BNAD_NAME);
	if (err)
		goto disable_device;
	if (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) {
		*using_dac = true;
	} else {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err)
			goto release_regions;
		*using_dac = false;
	}
	pci_set_master(pdev);
	return 0;

release_regions:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);

	return err;
}