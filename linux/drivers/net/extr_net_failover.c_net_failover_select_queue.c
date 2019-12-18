#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  queue_mapping; } ;
struct net_failover_info {int /*<<< orphan*/  primary_dev; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_select_queue ) (struct net_device*,struct sk_buff*,struct net_device*) ;} ;
struct net_device {int /*<<< orphan*/  real_num_tx_queues; struct net_device_ops* netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  slave_dev_queue_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_pick_tx (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 TYPE_1__* qdisc_skb_cb (struct sk_buff*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_rx_queue (struct sk_buff*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct sk_buff*,struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 net_failover_select_queue(struct net_device *dev,
				     struct sk_buff *skb,
				     struct net_device *sb_dev)
{
	struct net_failover_info *nfo_info = netdev_priv(dev);
	struct net_device *primary_dev;
	u16 txq;

	primary_dev = rcu_dereference(nfo_info->primary_dev);
	if (primary_dev) {
		const struct net_device_ops *ops = primary_dev->netdev_ops;

		if (ops->ndo_select_queue)
			txq = ops->ndo_select_queue(primary_dev, skb, sb_dev);
		else
			txq = netdev_pick_tx(primary_dev, skb, NULL);

		qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb->queue_mapping;

		return txq;
	}

	txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) : 0;

	/* Save the original txq to restore before passing to the driver */
	qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb->queue_mapping;

	if (unlikely(txq >= dev->real_num_tx_queues)) {
		do {
			txq -= dev->real_num_tx_queues;
		} while (txq >= dev->real_num_tx_queues);
	}

	return txq;
}