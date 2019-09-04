#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct page {int dummy; } ;
struct bnad_rx_unmap_q {size_t alloc_order; size_t reuse_pi; size_t map_size; struct bnad_rx_unmap* unmap; } ;
struct TYPE_6__ {size_t len; } ;
struct bnad_rx_unmap {size_t page_offset; TYPE_3__ vector; struct page* page; } ;
struct bnad {TYPE_1__* pcidev; } ;
struct bna_rxq_entry {int /*<<< orphan*/  host_addr; } ;
struct bna_rcb {size_t producer_index; size_t q_depth; int /*<<< orphan*/  flags; scalar_t__ sw_q; TYPE_2__* rxq; struct bnad_rx_unmap_q* unmap_q; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  rxbuf_map_failed; int /*<<< orphan*/  rxbuf_alloc_failed; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RXQ_POST_OK ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNA_QE_INDX_INC (size_t,size_t) ; 
 int /*<<< orphan*/  BNA_SET_DMA_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int GFP_ATOMIC ; 
 size_t PAGE_SIZE ; 
 int __GFP_COMP ; 
 struct page* alloc_pages (int,size_t) ; 
 int /*<<< orphan*/  bna_rxq_prod_indx_doorbell (struct bna_rcb*) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,struct page*,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ likely (size_t) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rxbuf_alloc_failed ; 
 int /*<<< orphan*/  rxbuf_map_failed ; 
 int /*<<< orphan*/  smp_mb () ; 
 size_t test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32
bnad_rxq_refill_page(struct bnad *bnad, struct bna_rcb *rcb, u32 nalloc)
{
	u32 alloced, prod, q_depth;
	struct bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	struct bnad_rx_unmap *unmap, *prev;
	struct bna_rxq_entry *rxent;
	struct page *page;
	u32 page_offset, alloc_size;
	dma_addr_t dma_addr;

	prod = rcb->producer_index;
	q_depth = rcb->q_depth;

	alloc_size = PAGE_SIZE << unmap_q->alloc_order;
	alloced = 0;

	while (nalloc--) {
		unmap = &unmap_q->unmap[prod];

		if (unmap_q->reuse_pi < 0) {
			page = alloc_pages(GFP_ATOMIC | __GFP_COMP,
					unmap_q->alloc_order);
			page_offset = 0;
		} else {
			prev = &unmap_q->unmap[unmap_q->reuse_pi];
			page = prev->page;
			page_offset = prev->page_offset + unmap_q->map_size;
			get_page(page);
		}

		if (unlikely(!page)) {
			BNAD_UPDATE_CTR(bnad, rxbuf_alloc_failed);
			rcb->rxq->rxbuf_alloc_failed++;
			goto finishing;
		}

		dma_addr = dma_map_page(&bnad->pcidev->dev, page, page_offset,
					unmap_q->map_size, DMA_FROM_DEVICE);
		if (dma_mapping_error(&bnad->pcidev->dev, dma_addr)) {
			put_page(page);
			BNAD_UPDATE_CTR(bnad, rxbuf_map_failed);
			rcb->rxq->rxbuf_map_failed++;
			goto finishing;
		}

		unmap->page = page;
		unmap->page_offset = page_offset;
		dma_unmap_addr_set(&unmap->vector, dma_addr, dma_addr);
		unmap->vector.len = unmap_q->map_size;
		page_offset += unmap_q->map_size;

		if (page_offset < alloc_size)
			unmap_q->reuse_pi = prod;
		else
			unmap_q->reuse_pi = -1;

		rxent = &((struct bna_rxq_entry *)rcb->sw_q)[prod];
		BNA_SET_DMA_ADDR(dma_addr, &rxent->host_addr);
		BNA_QE_INDX_INC(prod, q_depth);
		alloced++;
	}

finishing:
	if (likely(alloced)) {
		rcb->producer_index = prod;
		smp_mb();
		if (likely(test_bit(BNAD_RXQ_POST_OK, &rcb->flags)))
			bna_rxq_prod_indx_doorbell(rcb);
	}

	return alloced;
}