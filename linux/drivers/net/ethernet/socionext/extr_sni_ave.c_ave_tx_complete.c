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
struct net_device {int dummy; } ;
struct TYPE_5__ {unsigned int packets; unsigned int bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  collisions; int /*<<< orphan*/  errors; } ;
struct TYPE_4__ {int proc_idx; int done_idx; int ndesc; TYPE_3__* desc; } ;
struct ave_private {TYPE_2__ stats_tx; TYPE_1__ tx; } ;
struct TYPE_6__ {int /*<<< orphan*/ * skbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESCID_TX ; 
 int AVE_STS_EC ; 
 int AVE_STS_LAST ; 
 int AVE_STS_OK ; 
 int AVE_STS_OWC ; 
 int AVE_STS_OWN ; 
 int AVE_STS_PKTLEN_TX_MASK ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ave_desc_read_cmdsts (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ave_dma_unmap (struct net_device*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ave_tx_complete(struct net_device *ndev)
{
	struct ave_private *priv = netdev_priv(ndev);
	u32 proc_idx, done_idx, ndesc, cmdsts;
	unsigned int nr_freebuf = 0;
	unsigned int tx_packets = 0;
	unsigned int tx_bytes = 0;

	proc_idx = priv->tx.proc_idx;
	done_idx = priv->tx.done_idx;
	ndesc    = priv->tx.ndesc;

	/* free pre-stored skb from done_idx to proc_idx */
	while (proc_idx != done_idx) {
		cmdsts = ave_desc_read_cmdsts(ndev, AVE_DESCID_TX, done_idx);

		/* do nothing if owner is HW (==1 for Tx) */
		if (cmdsts & AVE_STS_OWN)
			break;

		/* check Tx status and updates statistics */
		if (cmdsts & AVE_STS_OK) {
			tx_bytes += cmdsts & AVE_STS_PKTLEN_TX_MASK;
			/* success */
			if (cmdsts & AVE_STS_LAST)
				tx_packets++;
		} else {
			/* error */
			if (cmdsts & AVE_STS_LAST) {
				priv->stats_tx.errors++;
				if (cmdsts & (AVE_STS_OWC | AVE_STS_EC))
					priv->stats_tx.collisions++;
			}
		}

		/* release skb */
		if (priv->tx.desc[done_idx].skbs) {
			ave_dma_unmap(ndev, &priv->tx.desc[done_idx],
				      DMA_TO_DEVICE);
			dev_consume_skb_any(priv->tx.desc[done_idx].skbs);
			priv->tx.desc[done_idx].skbs = NULL;
			nr_freebuf++;
		}
		done_idx = (done_idx + 1) % ndesc;
	}

	priv->tx.done_idx = done_idx;

	/* update stats */
	u64_stats_update_begin(&priv->stats_tx.syncp);
	priv->stats_tx.packets += tx_packets;
	priv->stats_tx.bytes   += tx_bytes;
	u64_stats_update_end(&priv->stats_tx.syncp);

	/* wake queue for freeing buffer */
	if (unlikely(netif_queue_stopped(ndev)) && nr_freebuf)
		netif_wake_queue(ndev);

	return nr_freebuf;
}