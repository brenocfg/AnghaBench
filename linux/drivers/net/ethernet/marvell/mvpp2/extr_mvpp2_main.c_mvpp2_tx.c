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
typedef  int u32 ;
typedef  size_t u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ stats; TYPE_1__ dev; } ;
struct mvpp2_txq_pcpu {int reserved_num; int count; int stop_threshold; } ;
struct mvpp2_tx_queue {int count; int done_pkts_coal; int /*<<< orphan*/  id; int /*<<< orphan*/  pcpu; } ;
struct mvpp2_tx_desc {int dummy; } ;
struct mvpp2_port_pcpu {int timer_scheduled; int /*<<< orphan*/  tx_done_timer; } ;
struct mvpp2_port {int /*<<< orphan*/ * tx_lock; TYPE_4__* priv; int /*<<< orphan*/  pcpu; int /*<<< orphan*/  has_tx_irqs; int /*<<< orphan*/  stats; struct mvpp2_tx_queue** txqs; } ;
struct mvpp2_pcpu_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock_map; struct mvpp2_tx_queue* aggr_txqs; } ;
struct TYPE_7__ {int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED_SOFT ; 
 int /*<<< orphan*/  MVPP2_TXDONE_HRTIMER_PERIOD_NS ; 
 int MVPP2_TXD_F_DESC ; 
 int MVPP2_TXD_L_DESC ; 
 int MVPP2_TXD_PADDING_DISABLE ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mvpp2_aggr_desc_num_check (struct mvpp2_port*,struct mvpp2_tx_queue*,int) ; 
 int /*<<< orphan*/  mvpp2_aggr_txq_pend_desc_add (struct mvpp2_port*,int) ; 
 unsigned int mvpp2_cpu_to_thread (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int mvpp2_skb_tx_csum (struct mvpp2_port*,struct sk_buff*) ; 
 scalar_t__ mvpp2_tx_frag_process (struct mvpp2_port*,struct sk_buff*,struct mvpp2_tx_queue*,struct mvpp2_tx_queue*) ; 
 int mvpp2_tx_tso (struct sk_buff*,struct net_device*,struct mvpp2_tx_queue*,struct mvpp2_tx_queue*,struct mvpp2_txq_pcpu*) ; 
 int /*<<< orphan*/  mvpp2_txdesc_cmd_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int) ; 
 int /*<<< orphan*/  mvpp2_txdesc_dma_addr_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txdesc_size_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txdesc_txq_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txq_desc_put (struct mvpp2_tx_queue*) ; 
 int /*<<< orphan*/  mvpp2_txq_done (struct mvpp2_port*,struct mvpp2_tx_queue*,struct mvpp2_txq_pcpu*) ; 
 int /*<<< orphan*/  mvpp2_txq_inc_put (struct mvpp2_port*,struct mvpp2_txq_pcpu*,struct sk_buff*,struct mvpp2_tx_desc*) ; 
 struct mvpp2_tx_desc* mvpp2_txq_next_desc_get (struct mvpp2_tx_queue*) ; 
 scalar_t__ mvpp2_txq_reserved_desc_num_proc (struct mvpp2_port*,struct mvpp2_tx_queue*,struct mvpp2_txq_pcpu*,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,size_t) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 void* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_desc_unmap_put (struct mvpp2_port*,struct mvpp2_tx_queue*,struct mvpp2_tx_desc*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t mvpp2_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct mvpp2_port *port = netdev_priv(dev);
	struct mvpp2_tx_queue *txq, *aggr_txq;
	struct mvpp2_txq_pcpu *txq_pcpu;
	struct mvpp2_tx_desc *tx_desc;
	dma_addr_t buf_dma_addr;
	unsigned long flags = 0;
	unsigned int thread;
	int frags = 0;
	u16 txq_id;
	u32 tx_cmd;

	thread = mvpp2_cpu_to_thread(port->priv, smp_processor_id());

	txq_id = skb_get_queue_mapping(skb);
	txq = port->txqs[txq_id];
	txq_pcpu = per_cpu_ptr(txq->pcpu, thread);
	aggr_txq = &port->priv->aggr_txqs[thread];

	if (test_bit(thread, &port->priv->lock_map))
		spin_lock_irqsave(&port->tx_lock[thread], flags);

	if (skb_is_gso(skb)) {
		frags = mvpp2_tx_tso(skb, dev, txq, aggr_txq, txq_pcpu);
		goto out;
	}
	frags = skb_shinfo(skb)->nr_frags + 1;

	/* Check number of available descriptors */
	if (mvpp2_aggr_desc_num_check(port, aggr_txq, frags) ||
	    mvpp2_txq_reserved_desc_num_proc(port, txq, txq_pcpu, frags)) {
		frags = 0;
		goto out;
	}

	/* Get a descriptor for the first part of the packet */
	tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
	mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
	mvpp2_txdesc_size_set(port, tx_desc, skb_headlen(skb));

	buf_dma_addr = dma_map_single(dev->dev.parent, skb->data,
				      skb_headlen(skb), DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(dev->dev.parent, buf_dma_addr))) {
		mvpp2_txq_desc_put(txq);
		frags = 0;
		goto out;
	}

	mvpp2_txdesc_dma_addr_set(port, tx_desc, buf_dma_addr);

	tx_cmd = mvpp2_skb_tx_csum(port, skb);

	if (frags == 1) {
		/* First and Last descriptor */
		tx_cmd |= MVPP2_TXD_F_DESC | MVPP2_TXD_L_DESC;
		mvpp2_txdesc_cmd_set(port, tx_desc, tx_cmd);
		mvpp2_txq_inc_put(port, txq_pcpu, skb, tx_desc);
	} else {
		/* First but not Last */
		tx_cmd |= MVPP2_TXD_F_DESC | MVPP2_TXD_PADDING_DISABLE;
		mvpp2_txdesc_cmd_set(port, tx_desc, tx_cmd);
		mvpp2_txq_inc_put(port, txq_pcpu, NULL, tx_desc);

		/* Continue with other skb fragments */
		if (mvpp2_tx_frag_process(port, skb, aggr_txq, txq)) {
			tx_desc_unmap_put(port, txq, tx_desc);
			frags = 0;
		}
	}

out:
	if (frags > 0) {
		struct mvpp2_pcpu_stats *stats = per_cpu_ptr(port->stats, thread);
		struct netdev_queue *nq = netdev_get_tx_queue(dev, txq_id);

		txq_pcpu->reserved_num -= frags;
		txq_pcpu->count += frags;
		aggr_txq->count += frags;

		/* Enable transmit */
		wmb();
		mvpp2_aggr_txq_pend_desc_add(port, frags);

		if (txq_pcpu->count >= txq_pcpu->stop_threshold)
			netif_tx_stop_queue(nq);

		u64_stats_update_begin(&stats->syncp);
		stats->tx_packets++;
		stats->tx_bytes += skb->len;
		u64_stats_update_end(&stats->syncp);
	} else {
		dev->stats.tx_dropped++;
		dev_kfree_skb_any(skb);
	}

	/* Finalize TX processing */
	if (!port->has_tx_irqs && txq_pcpu->count >= txq->done_pkts_coal)
		mvpp2_txq_done(port, txq, txq_pcpu);

	/* Set the timer in case not all frags were processed */
	if (!port->has_tx_irqs && txq_pcpu->count <= frags &&
	    txq_pcpu->count > 0) {
		struct mvpp2_port_pcpu *port_pcpu = per_cpu_ptr(port->pcpu, thread);

		if (!port_pcpu->timer_scheduled) {
			port_pcpu->timer_scheduled = true;
			hrtimer_start(&port_pcpu->tx_done_timer,
				      MVPP2_TXDONE_HRTIMER_PERIOD_NS,
				      HRTIMER_MODE_REL_PINNED_SOFT);
		}
	}

	if (test_bit(thread, &port->priv->lock_map))
		spin_unlock_irqrestore(&port->tx_lock[thread], flags);

	return NETDEV_TX_OK;
}