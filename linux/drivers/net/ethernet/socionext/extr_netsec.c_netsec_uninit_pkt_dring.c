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
typedef  size_t u16 ;
struct page {int dummy; } ;
struct netsec_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  dev; struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {scalar_t__ tail; scalar_t__ head; struct netsec_desc* vaddr; struct netsec_desc* desc; int /*<<< orphan*/  page_pool; int /*<<< orphan*/  xdp_rxq; } ;
struct netsec_desc {int /*<<< orphan*/  skb; int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 size_t DESC_NUM ; 
 size_t DESC_SZ ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NETSEC_RING_RX ; 
 int NETSEC_RING_TX ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct netsec_desc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pool_put_page (int /*<<< orphan*/ ,struct page*,int) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 
 scalar_t__ xdp_rxq_info_is_reg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netsec_uninit_pkt_dring(struct netsec_priv *priv, int id)
{
	struct netsec_desc_ring *dring = &priv->desc_ring[id];
	struct netsec_desc *desc;
	u16 idx;

	if (!dring->vaddr || !dring->desc)
		return;
	for (idx = 0; idx < DESC_NUM; idx++) {
		desc = &dring->desc[idx];
		if (!desc->addr)
			continue;

		if (id == NETSEC_RING_RX) {
			struct page *page = virt_to_page(desc->addr);

			page_pool_put_page(dring->page_pool, page, false);
		} else if (id == NETSEC_RING_TX) {
			dma_unmap_single(priv->dev, desc->dma_addr, desc->len,
					 DMA_TO_DEVICE);
			dev_kfree_skb(desc->skb);
		}
	}

	/* Rx is currently using page_pool */
	if (id == NETSEC_RING_RX) {
		if (xdp_rxq_info_is_reg(&dring->xdp_rxq))
			xdp_rxq_info_unreg(&dring->xdp_rxq);
		page_pool_destroy(dring->page_pool);
	}

	memset(dring->desc, 0, sizeof(struct netsec_desc) * DESC_NUM);
	memset(dring->vaddr, 0, DESC_SZ * DESC_NUM);

	dring->head = 0;
	dring->tail = 0;

	if (id == NETSEC_RING_TX)
		netdev_reset_queue(priv->ndev);
}