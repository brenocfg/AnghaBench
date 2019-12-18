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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;
struct hl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_mask; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 

int hl_pci_set_dma_mask(struct hl_device *hdev, u8 dma_mask)
{
	struct pci_dev *pdev = hdev->pdev;
	int rc;

	/* set DMA mask */
	rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(dma_mask));
	if (rc) {
		dev_warn(hdev->dev,
			"Failed to set pci dma mask to %d bits, error %d\n",
			dma_mask, rc);

		dma_mask = hdev->dma_mask;

		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(dma_mask));
		if (rc) {
			dev_err(hdev->dev,
				"Failed to set pci dma mask to %d bits, error %d\n",
				dma_mask, rc);
			return rc;
		}
	}

	/*
	 * We managed to set the dma mask, so update the dma mask field. If
	 * the set to the coherent mask will fail with that mask, we will
	 * fail the entire function
	 */
	hdev->dma_mask = dma_mask;

	rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(dma_mask));
	if (rc) {
		dev_err(hdev->dev,
			"Failed to set pci consistent dma mask to %d bits, error %d\n",
			dma_mask, rc);
		return rc;
	}

	return 0;
}