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
typedef  int u32 ;
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int proc_idx; int done_idx; int ndesc; TYPE_3__* desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dropped; } ;
struct ave_private {TYPE_2__ tx; TYPE_1__ stats_tx; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {struct sk_buff* skbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESCID_TX ; 
 int AVE_FORCE_TXINTCNT ; 
 int AVE_STS_1ST ; 
 int AVE_STS_INTR ; 
 int AVE_STS_LAST ; 
 int AVE_STS_NOCSUM ; 
 int AVE_STS_OWN ; 
 int AVE_STS_PKTLEN_TX_MASK ; 
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ETH_ZLEN ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  ave_desc_write_addr (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ave_desc_write_cmdsts (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int ave_dma_map (struct net_device*,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_put_padto (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ave_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct ave_private *priv = netdev_priv(ndev);
	u32 proc_idx, done_idx, ndesc, cmdsts;
	int ret, freepkt;
	dma_addr_t paddr;

	proc_idx = priv->tx.proc_idx;
	done_idx = priv->tx.done_idx;
	ndesc = priv->tx.ndesc;
	freepkt = ((done_idx + ndesc - 1) - proc_idx) % ndesc;

	/* stop queue when not enough entry */
	if (unlikely(freepkt < 1)) {
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	/* add padding for short packet */
	if (skb_put_padto(skb, ETH_ZLEN)) {
		priv->stats_tx.dropped++;
		return NETDEV_TX_OK;
	}

	/* map Tx buffer
	 * Tx buffer set to the Tx descriptor doesn't have any restriction.
	 */
	ret = ave_dma_map(ndev, &priv->tx.desc[proc_idx],
			  skb->data, skb->len, DMA_TO_DEVICE, &paddr);
	if (ret) {
		dev_kfree_skb_any(skb);
		priv->stats_tx.dropped++;
		return NETDEV_TX_OK;
	}

	priv->tx.desc[proc_idx].skbs = skb;

	ave_desc_write_addr(ndev, AVE_DESCID_TX, proc_idx, paddr);

	cmdsts = AVE_STS_OWN | AVE_STS_1ST | AVE_STS_LAST |
		(skb->len & AVE_STS_PKTLEN_TX_MASK);

	/* set interrupt per AVE_FORCE_TXINTCNT or when queue is stopped */
	if (!(proc_idx % AVE_FORCE_TXINTCNT) || netif_queue_stopped(ndev))
		cmdsts |= AVE_STS_INTR;

	/* disable checksum calculation when skb doesn't calurate checksum */
	if (skb->ip_summed == CHECKSUM_NONE ||
	    skb->ip_summed == CHECKSUM_UNNECESSARY)
		cmdsts |= AVE_STS_NOCSUM;

	ave_desc_write_cmdsts(ndev, AVE_DESCID_TX, proc_idx, cmdsts);

	priv->tx.proc_idx = (proc_idx + 1) % ndesc;

	return NETDEV_TX_OK;
}