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
struct sk_buff {scalar_t__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cmdQ_full; } ;
struct sge {scalar_t__ tx_sched; TYPE_1__ stats; int /*<<< orphan*/  stopped_tx_queues; struct cmdQ* cmdQ; } ;
struct net_device {int /*<<< orphan*/  if_port; } ;
struct cmdQ {unsigned int pidx; unsigned int size; unsigned int in_use; unsigned int stop_thres; unsigned int genbit; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; } ;
struct adapter {scalar_t__ regs; int /*<<< orphan*/  name; struct sge* sge; } ;
struct TYPE_4__ {int nr_frags; } ;

/* Variables and functions */
 scalar_t__ A_SG_DOORBELL ; 
 int /*<<< orphan*/  CMDQ_STAT_LAST_PKT_DB ; 
 int /*<<< orphan*/  CMDQ_STAT_RUNNING ; 
 int /*<<< orphan*/  F_CMDQ0_ENABLE ; 
 int /*<<< orphan*/  F_CMDQ1_ENABLE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ compute_large_page_tx_descs (struct sk_buff*) ; 
 int /*<<< orphan*/  doorbell_pio (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct sge*,struct cmdQ*) ; 
 struct sk_buff* sched_skb (struct sge*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_tx_descs (struct adapter*,struct sk_buff*,unsigned int,unsigned int,struct cmdQ*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int t1_sge_tx(struct sk_buff *skb, struct adapter *adapter,
		     unsigned int qid, struct net_device *dev)
{
	struct sge *sge = adapter->sge;
	struct cmdQ *q = &sge->cmdQ[qid];
	unsigned int credits, pidx, genbit, count, use_sched_skb = 0;

	spin_lock(&q->lock);

	reclaim_completed_tx(sge, q);

	pidx = q->pidx;
	credits = q->size - q->in_use;
	count = 1 + skb_shinfo(skb)->nr_frags;
	count += compute_large_page_tx_descs(skb);

	/* Ethernet packet */
	if (unlikely(credits < count)) {
		if (!netif_queue_stopped(dev)) {
			netif_stop_queue(dev);
			set_bit(dev->if_port, &sge->stopped_tx_queues);
			sge->stats.cmdQ_full[2]++;
			pr_err("%s: Tx ring full while queue awake!\n",
			       adapter->name);
		}
		spin_unlock(&q->lock);
		return NETDEV_TX_BUSY;
	}

	if (unlikely(credits - count < q->stop_thres)) {
		netif_stop_queue(dev);
		set_bit(dev->if_port, &sge->stopped_tx_queues);
		sge->stats.cmdQ_full[2]++;
	}

	/* T204 cmdQ0 skbs that are destined for a certain port have to go
	 * through the scheduler.
	 */
	if (sge->tx_sched && !qid && skb->dev) {
use_sched:
		use_sched_skb = 1;
		/* Note that the scheduler might return a different skb than
		 * the one passed in.
		 */
		skb = sched_skb(sge, skb, credits);
		if (!skb) {
			spin_unlock(&q->lock);
			return NETDEV_TX_OK;
		}
		pidx = q->pidx;
		count = 1 + skb_shinfo(skb)->nr_frags;
		count += compute_large_page_tx_descs(skb);
	}

	q->in_use += count;
	genbit = q->genbit;
	pidx = q->pidx;
	q->pidx += count;
	if (q->pidx >= q->size) {
		q->pidx -= q->size;
		q->genbit ^= 1;
	}
	spin_unlock(&q->lock);

	write_tx_descs(adapter, skb, pidx, genbit, q);

	/*
	 * We always ring the doorbell for cmdQ1.  For cmdQ0, we only ring
	 * the doorbell if the Q is asleep. There is a natural race, where
	 * the hardware is going to sleep just after we checked, however,
	 * then the interrupt handler will detect the outstanding TX packet
	 * and ring the doorbell for us.
	 */
	if (qid)
		doorbell_pio(adapter, F_CMDQ1_ENABLE);
	else {
		clear_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
		if (test_and_set_bit(CMDQ_STAT_RUNNING, &q->status) == 0) {
			set_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
			writel(F_CMDQ0_ENABLE, adapter->regs + A_SG_DOORBELL);
		}
	}

	if (use_sched_skb) {
		if (spin_trylock(&q->lock)) {
			credits = q->size - q->in_use;
			skb = NULL;
			goto use_sched;
		}
	}
	return NETDEV_TX_OK;
}