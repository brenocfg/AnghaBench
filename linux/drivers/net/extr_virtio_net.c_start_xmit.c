#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct virtnet_info {struct send_queue* sq; } ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  syncp; int /*<<< orphan*/  kicks; } ;
struct TYPE_8__ {int weight; } ;
struct send_queue {TYPE_3__ stats; TYPE_4__* vq; TYPE_1__ napi; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_fifo_errors; } ;
struct net_device {TYPE_2__ stats; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_11__ {scalar_t__ num_free; } ;

/* Variables and functions */
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  free_old_xmit_skbs (struct send_queue*,int) ; 
 scalar_t__ net_ratelimit () ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_start_subqueue (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_stop_subqueue (struct net_device*,int) ; 
 scalar_t__ netif_xmit_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (TYPE_4__*) ; 
 int /*<<< orphan*/  virtqueue_enable_cb_delayed (TYPE_4__*) ; 
 scalar_t__ virtqueue_kick_prepare (TYPE_4__*) ; 
 scalar_t__ virtqueue_notify (TYPE_4__*) ; 
 int xmit_skb (struct send_queue*,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct virtnet_info *vi = netdev_priv(dev);
	int qnum = skb_get_queue_mapping(skb);
	struct send_queue *sq = &vi->sq[qnum];
	int err;
	struct netdev_queue *txq = netdev_get_tx_queue(dev, qnum);
	bool kick = !netdev_xmit_more();
	bool use_napi = sq->napi.weight;

	/* Free up any pending old buffers before queueing new ones. */
	free_old_xmit_skbs(sq, false);

	if (use_napi && kick)
		virtqueue_enable_cb_delayed(sq->vq);

	/* timestamp packet in software */
	skb_tx_timestamp(skb);

	/* Try to transmit */
	err = xmit_skb(sq, skb);

	/* This should not happen! */
	if (unlikely(err)) {
		dev->stats.tx_fifo_errors++;
		if (net_ratelimit())
			dev_warn(&dev->dev,
				 "Unexpected TXQ (%d) queue failure: %d\n",
				 qnum, err);
		dev->stats.tx_dropped++;
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	/* Don't wait up for transmitted skbs to be freed. */
	if (!use_napi) {
		skb_orphan(skb);
		nf_reset_ct(skb);
	}

	/* If running out of space, stop queue to avoid getting packets that we
	 * are then unable to transmit.
	 * An alternative would be to force queuing layer to requeue the skb by
	 * returning NETDEV_TX_BUSY. However, NETDEV_TX_BUSY should not be
	 * returned in a normal path of operation: it means that driver is not
	 * maintaining the TX queue stop/start state properly, and causes
	 * the stack to do a non-trivial amount of useless work.
	 * Since most packets only take 1 or 2 ring slots, stopping the queue
	 * early means 16 slots are typically wasted.
	 */
	if (sq->vq->num_free < 2+MAX_SKB_FRAGS) {
		netif_stop_subqueue(dev, qnum);
		if (!use_napi &&
		    unlikely(!virtqueue_enable_cb_delayed(sq->vq))) {
			/* More just got used, free them then recheck. */
			free_old_xmit_skbs(sq, false);
			if (sq->vq->num_free >= 2+MAX_SKB_FRAGS) {
				netif_start_subqueue(dev, qnum);
				virtqueue_disable_cb(sq->vq);
			}
		}
	}

	if (kick || netif_xmit_stopped(txq)) {
		if (virtqueue_kick_prepare(sq->vq) && virtqueue_notify(sq->vq)) {
			u64_stats_update_begin(&sq->stats.syncp);
			sq->stats.kicks++;
			u64_stats_update_end(&sq->stats.syncp);
		}
	}

	return NETDEV_TX_OK;
}