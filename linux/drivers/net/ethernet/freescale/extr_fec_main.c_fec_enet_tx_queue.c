#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct fec_enet_private {scalar_t__ bufdesc_ex; TYPE_1__* pdev; struct fec_enet_priv_tx_q** tx_queue; } ;
struct TYPE_9__ {int /*<<< orphan*/  reg_desc_active; struct bufdesc* cur; } ;
struct fec_enet_priv_tx_q {int tx_wake_threshold; TYPE_4__ bd; struct bufdesc* dirty_tx; struct sk_buff** tx_skbuff; } ;
struct bufdesc_ex {int /*<<< orphan*/  ts; } ;
struct bufdesc {int /*<<< orphan*/  cbd_bufaddr; struct bufdesc* cbd_datlen; struct bufdesc* cbd_sc; } ;
struct TYPE_8__ {int tx_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short BD_ENET_TX_CSL ; 
 unsigned short BD_ENET_TX_DEF ; 
 unsigned short BD_ENET_TX_HB ; 
 unsigned short BD_ENET_TX_LC ; 
 unsigned short BD_ENET_TX_READY ; 
 unsigned short BD_ENET_TX_RL ; 
 unsigned short BD_ENET_TX_UN ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t FEC_ENET_GET_QUQUE (size_t) ; 
 int /*<<< orphan*/  IS_TSO_HEADER (struct fec_enet_priv_tx_q*,int /*<<< orphan*/ ) ; 
 struct bufdesc* READ_ONCE (struct bufdesc*) ; 
 int SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  cpu_to_fec32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 unsigned short fec16_to_cpu (struct bufdesc*) ; 
 int /*<<< orphan*/  fec32_to_cpu (int /*<<< orphan*/ ) ; 
 int fec_enet_get_bd_index (struct bufdesc*,TYPE_4__*) ; 
 int fec_enet_get_free_txdesc_num (struct fec_enet_priv_tx_q*) ; 
 struct bufdesc* fec_enet_get_nextdesc (struct bufdesc*,TYPE_4__*) ; 
 int /*<<< orphan*/  fec_enet_hwtstamp (struct fec_enet_private*,int /*<<< orphan*/ ,struct skb_shared_hwtstamps*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,size_t) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fec_enet_tx_queue(struct net_device *ndev, u16 queue_id)
{
	struct	fec_enet_private *fep;
	struct bufdesc *bdp;
	unsigned short status;
	struct	sk_buff	*skb;
	struct fec_enet_priv_tx_q *txq;
	struct netdev_queue *nq;
	int	index = 0;
	int	entries_free;

	fep = netdev_priv(ndev);

	queue_id = FEC_ENET_GET_QUQUE(queue_id);

	txq = fep->tx_queue[queue_id];
	/* get next bdp of dirty_tx */
	nq = netdev_get_tx_queue(ndev, queue_id);
	bdp = txq->dirty_tx;

	/* get next bdp of dirty_tx */
	bdp = fec_enet_get_nextdesc(bdp, &txq->bd);

	while (bdp != READ_ONCE(txq->bd.cur)) {
		/* Order the load of bd.cur and cbd_sc */
		rmb();
		status = fec16_to_cpu(READ_ONCE(bdp->cbd_sc));
		if (status & BD_ENET_TX_READY)
			break;

		index = fec_enet_get_bd_index(bdp, &txq->bd);

		skb = txq->tx_skbuff[index];
		txq->tx_skbuff[index] = NULL;
		if (!IS_TSO_HEADER(txq, fec32_to_cpu(bdp->cbd_bufaddr)))
			dma_unmap_single(&fep->pdev->dev,
					 fec32_to_cpu(bdp->cbd_bufaddr),
					 fec16_to_cpu(bdp->cbd_datlen),
					 DMA_TO_DEVICE);
		bdp->cbd_bufaddr = cpu_to_fec32(0);
		if (!skb)
			goto skb_done;

		/* Check for errors. */
		if (status & (BD_ENET_TX_HB | BD_ENET_TX_LC |
				   BD_ENET_TX_RL | BD_ENET_TX_UN |
				   BD_ENET_TX_CSL)) {
			ndev->stats.tx_errors++;
			if (status & BD_ENET_TX_HB)  /* No heartbeat */
				ndev->stats.tx_heartbeat_errors++;
			if (status & BD_ENET_TX_LC)  /* Late collision */
				ndev->stats.tx_window_errors++;
			if (status & BD_ENET_TX_RL)  /* Retrans limit */
				ndev->stats.tx_aborted_errors++;
			if (status & BD_ENET_TX_UN)  /* Underrun */
				ndev->stats.tx_fifo_errors++;
			if (status & BD_ENET_TX_CSL) /* Carrier lost */
				ndev->stats.tx_carrier_errors++;
		} else {
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += skb->len;
		}

		if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS) &&
			fep->bufdesc_ex) {
			struct skb_shared_hwtstamps shhwtstamps;
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;

			fec_enet_hwtstamp(fep, fec32_to_cpu(ebdp->ts), &shhwtstamps);
			skb_tstamp_tx(skb, &shhwtstamps);
		}

		/* Deferred means some collisions occurred during transmit,
		 * but we eventually sent the packet OK.
		 */
		if (status & BD_ENET_TX_DEF)
			ndev->stats.collisions++;

		/* Free the sk buffer associated with this last transmit */
		dev_kfree_skb_any(skb);
skb_done:
		/* Make sure the update to bdp and tx_skbuff are performed
		 * before dirty_tx
		 */
		wmb();
		txq->dirty_tx = bdp;

		/* Update pointer to next buffer descriptor to be transmitted */
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);

		/* Since we have freed up a buffer, the ring is no longer full
		 */
		if (netif_tx_queue_stopped(nq)) {
			entries_free = fec_enet_get_free_txdesc_num(txq);
			if (entries_free >= txq->tx_wake_threshold)
				netif_tx_wake_queue(nq);
		}
	}

	/* ERR006358: Keep the transmitter going */
	if (bdp != txq->bd.cur &&
	    readl(txq->bd.reg_desc_active) == 0)
		writel(0, txq->bd.reg_desc_active);
}