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
struct device {int dummy; } ;
struct aq_rxpage {unsigned int order; int /*<<< orphan*/ * page; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aq_free_rxpage(struct aq_rxpage *rxpage, struct device *dev)
{
	unsigned int len = PAGE_SIZE << rxpage->order;

	dma_unmap_page(dev, rxpage->daddr, len, DMA_FROM_DEVICE);

	/* Drop the ref for being in the ring. */
	__free_pages(rxpage->page, rxpage->order);
	rxpage->page = NULL;
}