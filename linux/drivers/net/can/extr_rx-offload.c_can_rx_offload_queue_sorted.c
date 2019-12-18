#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct can_rx_offload_cb {int /*<<< orphan*/  timestamp; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct can_rx_offload {scalar_t__ skb_queue_len_max; TYPE_1__ skb_queue; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  __skb_queue_add_sort (TYPE_1__*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_rx_offload_compare ; 
 struct can_rx_offload_cb* can_rx_offload_get_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  can_rx_offload_schedule (struct can_rx_offload*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_queue_len (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int can_rx_offload_queue_sorted(struct can_rx_offload *offload,
				struct sk_buff *skb, u32 timestamp)
{
	struct can_rx_offload_cb *cb;
	unsigned long flags;

	if (skb_queue_len(&offload->skb_queue) >
	    offload->skb_queue_len_max) {
		kfree_skb(skb);
		return -ENOBUFS;
	}

	cb = can_rx_offload_get_cb(skb);
	cb->timestamp = timestamp;

	spin_lock_irqsave(&offload->skb_queue.lock, flags);
	__skb_queue_add_sort(&offload->skb_queue, skb, can_rx_offload_compare);
	spin_unlock_irqrestore(&offload->skb_queue.lock, flags);

	can_rx_offload_schedule(offload);

	return 0;
}