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
struct ddb_dma {int num; int /*<<< orphan*/ ** vbuf; int /*<<< orphan*/ * pbuf; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __GFP_RETRY_MAYFAIL ; 
 scalar_t__ alt_dma ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_alloc(struct pci_dev *pdev, struct ddb_dma *dma, int dir)
{
	int i;

	if (!dma)
		return 0;
	for (i = 0; i < dma->num; i++) {
		if (alt_dma) {
			dma->vbuf[i] = kmalloc(dma->size, __GFP_RETRY_MAYFAIL);
			if (!dma->vbuf[i])
				return -ENOMEM;
			dma->pbuf[i] = dma_map_single(&pdev->dev,
						      dma->vbuf[i],
						      dma->size,
						      dir ? DMA_TO_DEVICE :
						      DMA_FROM_DEVICE);
			if (dma_mapping_error(&pdev->dev, dma->pbuf[i])) {
				kfree(dma->vbuf[i]);
				dma->vbuf[i] = NULL;
				return -ENOMEM;
			}
		} else {
			dma->vbuf[i] = dma_alloc_coherent(&pdev->dev,
							  dma->size,
							  &dma->pbuf[i],
							  GFP_KERNEL);
			if (!dma->vbuf[i])
				return -ENOMEM;
		}
	}
	return 0;
}