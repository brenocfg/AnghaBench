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
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  queue_mapping; } ;
struct net_device {scalar_t__ real_num_tx_queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  slave_dev_queue_mapping; } ;

/* Variables and functions */
 TYPE_1__* qdisc_skb_cb (struct sk_buff*) ; 
 scalar_t__ skb_get_rx_queue (struct sk_buff*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 team_select_queue(struct net_device *dev, struct sk_buff *skb,
			     struct net_device *sb_dev)
{
	/*
	 * This helper function exists to help dev_pick_tx get the correct
	 * destination queue.  Using a helper function skips a call to
	 * skb_tx_hash and will put the skbs in the queue we expect on their
	 * way down to the team driver.
	 */
	u16 txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) : 0;

	/*
	 * Save the original txq to restore before passing to the driver
	 */
	qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb->queue_mapping;

	if (unlikely(txq >= dev->real_num_tx_queues)) {
		do {
			txq -= dev->real_num_tx_queues;
		} while (txq >= dev->real_num_tx_queues);
	}
	return txq;
}