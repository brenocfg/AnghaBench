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
struct xge_raw_desc {int dummy; } ;
struct xge_pdata {struct xge_desc_ring* tx_ring; TYPE_1__* pdev; } ;
struct xge_desc_ring {TYPE_2__* pkt_info; struct xge_raw_desc* raw_desc; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {void* pkt_buf; int /*<<< orphan*/  dma_addr; struct sk_buff* skb; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int XGENE_ENET_NUM_DESC ; 
 int /*<<< orphan*/  XGENE_ENET_STD_MTU ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_tx_pending (struct xge_raw_desc*) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xge_free_pending_skb(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct device *dev = &pdata->pdev->dev;
	struct xge_desc_ring *tx_ring;
	struct xge_raw_desc *raw_desc;
	dma_addr_t dma_addr;
	struct sk_buff *skb;
	void *pkt_buf;
	int i;

	tx_ring = pdata->tx_ring;

	for (i = 0; i < XGENE_ENET_NUM_DESC; i++) {
		raw_desc = &tx_ring->raw_desc[i];

		if (!is_tx_pending(raw_desc))
			continue;

		skb = tx_ring->pkt_info[i].skb;
		dma_addr = tx_ring->pkt_info[i].dma_addr;
		pkt_buf = tx_ring->pkt_info[i].pkt_buf;
		dma_free_coherent(dev, XGENE_ENET_STD_MTU, pkt_buf, dma_addr);
		dev_kfree_skb_any(skb);
	}
}