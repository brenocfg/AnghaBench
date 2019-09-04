#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct mvneta_rx_queue {int dummy; } ;
struct mvneta_rx_desc {int dummy; } ;
struct mvneta_port {scalar_t__ rx_offset_correction; TYPE_2__* dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* __dev_alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_rx_desc_fill (struct mvneta_rx_desc*,int /*<<< orphan*/ ,struct page*,struct mvneta_rx_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvneta_rx_refill(struct mvneta_port *pp,
			    struct mvneta_rx_desc *rx_desc,
			    struct mvneta_rx_queue *rxq,
			    gfp_t gfp_mask)
{
	dma_addr_t phys_addr;
	struct page *page;

	page = __dev_alloc_page(gfp_mask);
	if (!page)
		return -ENOMEM;

	/* map page for use */
	phys_addr = dma_map_page(pp->dev->dev.parent, page, 0, PAGE_SIZE,
				 DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(pp->dev->dev.parent, phys_addr))) {
		__free_page(page);
		return -ENOMEM;
	}

	phys_addr += pp->rx_offset_correction;
	mvneta_rx_desc_fill(rx_desc, phys_addr, page, rxq);
	return 0;
}