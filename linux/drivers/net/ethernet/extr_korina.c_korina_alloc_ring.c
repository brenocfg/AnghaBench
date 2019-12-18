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
struct sk_buff {TYPE_2__* data; } ;
struct net_device {int dummy; } ;
struct korina_private {void* rx_chain_status; scalar_t__ rx_chain_tail; scalar_t__ rx_chain_head; scalar_t__ rx_next_done; TYPE_2__* rd_ring; struct sk_buff** rx_skb; void* tx_chain_status; scalar_t__ tx_count; scalar_t__ tx_full; scalar_t__ tx_chain_tail; scalar_t__ tx_chain_head; scalar_t__ tx_next_done; TYPE_1__* td_ring; } ;
struct TYPE_4__ {int control; void* link; void* ca; scalar_t__ devcs; } ;
struct TYPE_3__ {int devcs; scalar_t__ link; scalar_t__ ca; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 void* CPHYSADDR (TYPE_2__*) ; 
 int DMA_COUNT (int /*<<< orphan*/ ) ; 
 int DMA_DESC_COD ; 
 int DMA_DESC_IOD ; 
 int /*<<< orphan*/  DMA_DESC_IOF ; 
 int ENOMEM ; 
 int ETH_TX_FD ; 
 int ETH_TX_LD ; 
 int KORINA_NUM_RDS ; 
 int KORINA_NUM_TDS ; 
 int /*<<< orphan*/  KORINA_RBSIZE ; 
 void* desc_empty ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int korina_alloc_ring(struct net_device *dev)
{
	struct korina_private *lp = netdev_priv(dev);
	struct sk_buff *skb;
	int i;

	/* Initialize the transmit descriptors */
	for (i = 0; i < KORINA_NUM_TDS; i++) {
		lp->td_ring[i].control = DMA_DESC_IOF;
		lp->td_ring[i].devcs = ETH_TX_FD | ETH_TX_LD;
		lp->td_ring[i].ca = 0;
		lp->td_ring[i].link = 0;
	}
	lp->tx_next_done = lp->tx_chain_head = lp->tx_chain_tail =
			lp->tx_full = lp->tx_count = 0;
	lp->tx_chain_status = desc_empty;

	/* Initialize the receive descriptors */
	for (i = 0; i < KORINA_NUM_RDS; i++) {
		skb = netdev_alloc_skb_ip_align(dev, KORINA_RBSIZE);
		if (!skb)
			return -ENOMEM;
		lp->rx_skb[i] = skb;
		lp->rd_ring[i].control = DMA_DESC_IOD |
				DMA_COUNT(KORINA_RBSIZE);
		lp->rd_ring[i].devcs = 0;
		lp->rd_ring[i].ca = CPHYSADDR(skb->data);
		lp->rd_ring[i].link = CPHYSADDR(&lp->rd_ring[i+1]);
	}

	/* loop back receive descriptors, so the last
	 * descriptor points to the first one */
	lp->rd_ring[i - 1].link = CPHYSADDR(&lp->rd_ring[0]);
	lp->rd_ring[i - 1].control |= DMA_DESC_COD;

	lp->rx_next_done  = 0;
	lp->rx_chain_head = 0;
	lp->rx_chain_tail = 0;
	lp->rx_chain_status = desc_empty;

	return 0;
}