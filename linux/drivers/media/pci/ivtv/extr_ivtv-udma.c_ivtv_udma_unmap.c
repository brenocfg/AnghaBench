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
struct ivtv_user_dma {int page_count; int /*<<< orphan*/ * map; scalar_t__ SG_length; int /*<<< orphan*/  SGlist; } ;
struct ivtv {int /*<<< orphan*/  pdev; struct ivtv_user_dma udma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  ivtv_udma_sync_for_cpu (struct ivtv*) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

void ivtv_udma_unmap(struct ivtv *itv)
{
	struct ivtv_user_dma *dma = &itv->udma;
	int i;

	IVTV_DEBUG_INFO("ivtv_unmap_user_dma\n");

	/* Nothing to free */
	if (dma->page_count == 0)
		return;

	/* Unmap Scatterlist */
	if (dma->SG_length) {
		pci_unmap_sg(itv->pdev, dma->SGlist, dma->page_count, PCI_DMA_TODEVICE);
		dma->SG_length = 0;
	}
	/* sync DMA */
	ivtv_udma_sync_for_cpu(itv);

	/* Release User Pages */
	for (i = 0; i < dma->page_count; i++) {
		put_page(dma->map[i]);
	}
	dma->page_count = 0;
}