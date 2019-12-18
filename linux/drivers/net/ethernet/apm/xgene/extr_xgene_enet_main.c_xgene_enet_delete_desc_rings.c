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
struct xgene_enet_pdata {int txq_cnt; int rxq_cnt; struct xgene_enet_desc_ring** rx_ring; TYPE_1__* port_ops; struct xgene_enet_desc_ring** tx_ring; scalar_t__ cq_cnt; } ;
struct xgene_enet_desc_ring {struct xgene_enet_desc_ring* buf_pool; struct xgene_enet_desc_ring* page_pool; struct xgene_enet_desc_ring* cp_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear ) (struct xgene_enet_pdata*,struct xgene_enet_desc_ring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct xgene_enet_pdata*,struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  stub2 (struct xgene_enet_pdata*,struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  stub3 (struct xgene_enet_pdata*,struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  xgene_enet_delete_bufpool (struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  xgene_enet_delete_pagepool (struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  xgene_enet_delete_ring (struct xgene_enet_desc_ring*) ; 

__attribute__((used)) static void xgene_enet_delete_desc_rings(struct xgene_enet_pdata *pdata)
{
	struct xgene_enet_desc_ring *buf_pool, *page_pool;
	struct xgene_enet_desc_ring *ring;
	int i;

	for (i = 0; i < pdata->txq_cnt; i++) {
		ring = pdata->tx_ring[i];
		if (ring) {
			xgene_enet_delete_ring(ring);
			pdata->port_ops->clear(pdata, ring);
			if (pdata->cq_cnt)
				xgene_enet_delete_ring(ring->cp_ring);
			pdata->tx_ring[i] = NULL;
		}

	}

	for (i = 0; i < pdata->rxq_cnt; i++) {
		ring = pdata->rx_ring[i];
		if (ring) {
			page_pool = ring->page_pool;
			if (page_pool) {
				xgene_enet_delete_pagepool(page_pool);
				xgene_enet_delete_ring(page_pool);
				pdata->port_ops->clear(pdata, page_pool);
			}

			buf_pool = ring->buf_pool;
			xgene_enet_delete_bufpool(buf_pool);
			xgene_enet_delete_ring(buf_pool);
			pdata->port_ops->clear(pdata, buf_pool);

			xgene_enet_delete_ring(ring);
			pdata->rx_ring[i] = NULL;
		}

	}
}