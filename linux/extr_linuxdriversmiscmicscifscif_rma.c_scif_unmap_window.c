#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scif_window {int nr_contig_chunks; int* dma_addr; int* num_pages; TYPE_2__* st; } ;
struct scif_dev {TYPE_1__* sdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 scalar_t__ scif_is_iommu_enabled () ; 
 int /*<<< orphan*/  scif_unmap_single (int,struct scif_dev*,int) ; 
 int /*<<< orphan*/  scifdev_self (struct scif_dev*) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_2__*) ; 

void scif_unmap_window(struct scif_dev *remote_dev, struct scif_window *window)
{
	int j;

	if (scif_is_iommu_enabled() && !scifdev_self(remote_dev)) {
		if (window->st) {
			dma_unmap_sg(&remote_dev->sdev->dev,
				     window->st->sgl, window->st->nents,
				     DMA_BIDIRECTIONAL);
			sg_free_table(window->st);
			kfree(window->st);
			window->st = NULL;
		}
	} else {
		for (j = 0; j < window->nr_contig_chunks; j++) {
			if (window->dma_addr[j]) {
				scif_unmap_single(window->dma_addr[j],
						  remote_dev,
						  window->num_pages[j] <<
						  PAGE_SHIFT);
				window->dma_addr[j] = 0x0;
			}
		}
	}
}