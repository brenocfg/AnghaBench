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
struct snd_queue {int /*<<< orphan*/  free_cnt; } ;
struct sk_buff {scalar_t__ len; } ;
struct nicvf {TYPE_2__* drv_stats; TYPE_1__* qs; int /*<<< orphan*/  netdev; scalar_t__* snicvf; scalar_t__ xdp_tx_queues; scalar_t__ xdp_prog; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  txq_stop; } ;
struct TYPE_3__ {struct snd_queue* sq; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int MAX_SND_QUEUES_PER_QS ; 
 scalar_t__ MIN_SQ_DESC_PER_PKT_XMIT ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_warn (struct nicvf*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  nicvf_sq_append_skb (struct nicvf*,struct snd_queue*,struct sk_buff*,int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static netdev_tx_t nicvf_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct nicvf *nic = netdev_priv(netdev);
	int qid = skb_get_queue_mapping(skb);
	struct netdev_queue *txq = netdev_get_tx_queue(netdev, qid);
	struct nicvf *snic;
	struct snd_queue *sq;
	int tmp;

	/* Check for minimum packet length */
	if (skb->len <= ETH_HLEN) {
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	/* In XDP case, initial HW tx queues are used for XDP,
	 * but stack's queue mapping starts at '0', so skip the
	 * Tx queues attached to Rx queues for XDP.
	 */
	if (nic->xdp_prog)
		qid += nic->xdp_tx_queues;

	snic = nic;
	/* Get secondary Qset's SQ structure */
	if (qid >= MAX_SND_QUEUES_PER_QS) {
		tmp = qid / MAX_SND_QUEUES_PER_QS;
		snic = (struct nicvf *)nic->snicvf[tmp - 1];
		if (!snic) {
			netdev_warn(nic->netdev,
				    "Secondary Qset#%d's ptr not initialized\n",
				    tmp - 1);
			dev_kfree_skb(skb);
			return NETDEV_TX_OK;
		}
		qid = qid % MAX_SND_QUEUES_PER_QS;
	}

	sq = &snic->qs->sq[qid];
	if (!netif_tx_queue_stopped(txq) &&
	    !nicvf_sq_append_skb(snic, sq, skb, qid)) {
		netif_tx_stop_queue(txq);

		/* Barrier, so that stop_queue visible to other cpus */
		smp_mb();

		/* Check again, incase another cpu freed descriptors */
		if (atomic_read(&sq->free_cnt) > MIN_SQ_DESC_PER_PKT_XMIT) {
			netif_tx_wake_queue(txq);
		} else {
			this_cpu_inc(nic->drv_stats->txq_stop);
			netif_warn(nic, tx_err, netdev,
				   "Transmit ring full, stopping SQ%d\n", qid);
		}
		return NETDEV_TX_BUSY;
	}

	return NETDEV_TX_OK;
}