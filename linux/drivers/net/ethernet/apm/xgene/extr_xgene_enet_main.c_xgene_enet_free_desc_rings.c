#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xgene_enet_pdata {int txq_cnt; int rxq_cnt; struct xgene_enet_desc_ring** rx_ring; scalar_t__ cq_cnt; struct xgene_enet_desc_ring** tx_ring; TYPE_1__* pdev; } ;
struct xgene_enet_desc_ring {void* cp_skb; void* rx_skb; void* frag_dma_addr; void* frag_page; struct xgene_enet_desc_ring* page_pool; struct xgene_enet_desc_ring* buf_pool; struct xgene_enet_desc_ring* cp_ring; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (struct device*,void*) ; 
 int /*<<< orphan*/  xgene_enet_free_desc_ring (struct xgene_enet_desc_ring*) ; 

__attribute__((used)) static void xgene_enet_free_desc_rings(struct xgene_enet_pdata *pdata)
{
	struct xgene_enet_desc_ring *page_pool;
	struct device *dev = &pdata->pdev->dev;
	struct xgene_enet_desc_ring *ring;
	void *p;
	int i;

	for (i = 0; i < pdata->txq_cnt; i++) {
		ring = pdata->tx_ring[i];
		if (ring) {
			if (ring->cp_ring && ring->cp_ring->cp_skb)
				devm_kfree(dev, ring->cp_ring->cp_skb);

			if (ring->cp_ring && pdata->cq_cnt)
				xgene_enet_free_desc_ring(ring->cp_ring);

			xgene_enet_free_desc_ring(ring);
		}

	}

	for (i = 0; i < pdata->rxq_cnt; i++) {
		ring = pdata->rx_ring[i];
		if (ring) {
			if (ring->buf_pool) {
				if (ring->buf_pool->rx_skb)
					devm_kfree(dev, ring->buf_pool->rx_skb);

				xgene_enet_free_desc_ring(ring->buf_pool);
			}

			page_pool = ring->page_pool;
			if (page_pool) {
				p = page_pool->frag_page;
				if (p)
					devm_kfree(dev, p);

				p = page_pool->frag_dma_addr;
				if (p)
					devm_kfree(dev, p);
			}

			xgene_enet_free_desc_ring(ring);
		}
	}
}