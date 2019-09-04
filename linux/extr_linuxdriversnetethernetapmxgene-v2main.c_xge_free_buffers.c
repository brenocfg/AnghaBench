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
struct xge_pdata {TYPE_2__* pdev; struct xge_desc_ring* rx_ring; } ;
struct xge_desc_ring {TYPE_1__* pkt_info; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_addr; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int XGENE_ENET_NUM_DESC ; 
 int /*<<< orphan*/  XGENE_ENET_STD_MTU ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xge_free_buffers(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct xge_desc_ring *ring = pdata->rx_ring;
	struct device *dev = &pdata->pdev->dev;
	struct sk_buff *skb;
	dma_addr_t dma_addr;
	int i;

	for (i = 0; i < XGENE_ENET_NUM_DESC; i++) {
		skb = ring->pkt_info[i].skb;
		dma_addr = ring->pkt_info[i].dma_addr;

		if (!skb)
			continue;

		dma_unmap_single(dev, dma_addr, XGENE_ENET_STD_MTU,
				 DMA_FROM_DEVICE);
		dev_kfree_skb_any(skb);
	}
}