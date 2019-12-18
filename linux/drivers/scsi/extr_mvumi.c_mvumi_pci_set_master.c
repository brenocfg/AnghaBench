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
 scalar_t__ IS_DMA64 ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int mvumi_pci_set_master(struct pci_dev *pdev)
{
	int ret = 0;

	pci_set_master(pdev);

	if (IS_DMA64) {
		if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)))
			ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	} else
		ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));

	return ret;
}