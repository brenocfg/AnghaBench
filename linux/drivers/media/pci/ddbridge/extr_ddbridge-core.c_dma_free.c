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
 scalar_t__ alt_dma ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_free(struct pci_dev *pdev, struct ddb_dma *dma, int dir)
{
	int i;

	if (!dma)
		return;
	for (i = 0; i < dma->num; i++) {
		if (dma->vbuf[i]) {
			if (alt_dma) {
				dma_unmap_single(&pdev->dev, dma->pbuf[i],
						 dma->size,
						 dir ? DMA_TO_DEVICE :
						 DMA_FROM_DEVICE);
				kfree(dma->vbuf[i]);
				dma->vbuf[i] = NULL;
			} else {
				dma_free_coherent(&pdev->dev, dma->size,
						  dma->vbuf[i], dma->pbuf[i]);
			}

			dma->vbuf[i] = NULL;
		}
	}
}