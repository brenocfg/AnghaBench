#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct sgiseeq_private {TYPE_4__* rx_desc; TYPE_4__* tx_desc; scalar_t__ tx_old; scalar_t__ rx_old; scalar_t__ tx_new; scalar_t__ rx_new; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  cntinfo; int /*<<< orphan*/  pbuf; } ;
struct TYPE_5__ {int /*<<< orphan*/  cntinfo; } ;
struct TYPE_8__ {TYPE_3__ rdma; struct sk_buff* skb; TYPE_1__ tdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HPCDMA_EOR ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 int /*<<< orphan*/  RCNTINFO_INIT ; 
 int SEEQ_RX_BUFFERS ; 
 int SEEQ_TX_BUFFERS ; 
 int /*<<< orphan*/  TCNTINFO_INIT ; 
 int /*<<< orphan*/  __sgiseeq_set_mac_address (struct net_device*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_desc_dev (struct net_device*,TYPE_4__*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int seeq_init_ring(struct net_device *dev)
{
	struct sgiseeq_private *sp = netdev_priv(dev);
	int i;

	netif_stop_queue(dev);
	sp->rx_new = sp->tx_new = 0;
	sp->rx_old = sp->tx_old = 0;

	__sgiseeq_set_mac_address(dev);

	/* Setup tx ring. */
	for(i = 0; i < SEEQ_TX_BUFFERS; i++) {
		sp->tx_desc[i].tdma.cntinfo = TCNTINFO_INIT;
		dma_sync_desc_dev(dev, &sp->tx_desc[i]);
	}

	/* And now the rx ring. */
	for (i = 0; i < SEEQ_RX_BUFFERS; i++) {
		if (!sp->rx_desc[i].skb) {
			dma_addr_t dma_addr;
			struct sk_buff *skb = netdev_alloc_skb(dev, PKT_BUF_SZ);

			if (skb == NULL)
				return -ENOMEM;
			skb_reserve(skb, 2);
			dma_addr = dma_map_single(dev->dev.parent,
						  skb->data - 2,
						  PKT_BUF_SZ, DMA_FROM_DEVICE);
			sp->rx_desc[i].skb = skb;
			sp->rx_desc[i].rdma.pbuf = dma_addr;
		}
		sp->rx_desc[i].rdma.cntinfo = RCNTINFO_INIT;
		dma_sync_desc_dev(dev, &sp->rx_desc[i]);
	}
	sp->rx_desc[i - 1].rdma.cntinfo |= HPCDMA_EOR;
	dma_sync_desc_dev(dev, &sp->rx_desc[i - 1]);
	return 0;
}