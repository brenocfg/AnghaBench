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
struct efa_com_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  EFA_REGS_RESET_NORMAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int efa_com_dev_reset (struct efa_com_dev*,int /*<<< orphan*/ ) ; 
 int efa_com_get_dma_width (struct efa_com_dev*) ; 
 int efa_com_validate_version (struct efa_com_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efa_device_init(struct efa_com_dev *edev, struct pci_dev *pdev)
{
	int dma_width;
	int err;

	err = efa_com_dev_reset(edev, EFA_REGS_RESET_NORMAL);
	if (err)
		return err;

	err = efa_com_validate_version(edev);
	if (err)
		return err;

	dma_width = efa_com_get_dma_width(edev);
	if (dma_width < 0) {
		err = dma_width;
		return err;
	}

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(dma_width));
	if (err) {
		dev_err(&pdev->dev, "pci_set_dma_mask failed %d\n", err);
		return err;
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(dma_width));
	if (err) {
		dev_err(&pdev->dev,
			"err_pci_set_consistent_dma_mask failed %d\n",
			err);
		return err;
	}

	return 0;
}