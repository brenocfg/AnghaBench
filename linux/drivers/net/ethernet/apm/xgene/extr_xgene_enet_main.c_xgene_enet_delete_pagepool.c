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
struct xgene_enet_desc_ring {int slots; int /*<<< orphan*/ * frag_dma_addr; struct page** frag_page; int /*<<< orphan*/  ndev; } ;
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* ndev_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static void xgene_enet_delete_pagepool(struct xgene_enet_desc_ring *buf_pool)
{
	struct device *dev = ndev_to_dev(buf_pool->ndev);
	dma_addr_t dma_addr;
	struct page *page;
	int i;

	/* Free up the buffers held by hardware */
	for (i = 0; i < buf_pool->slots; i++) {
		page = buf_pool->frag_page[i];
		if (page) {
			dma_addr = buf_pool->frag_dma_addr[i];
			dma_unmap_page(dev, dma_addr, PAGE_SIZE,
				       DMA_FROM_DEVICE);
			put_page(page);
		}
	}
}