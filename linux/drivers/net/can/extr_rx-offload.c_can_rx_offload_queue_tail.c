#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct can_rx_offload {scalar_t__ skb_queue_len_max; int /*<<< orphan*/  skb_queue; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  can_rx_offload_schedule (struct can_rx_offload*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int can_rx_offload_queue_tail(struct can_rx_offload *offload,
			      struct sk_buff *skb)
{
	if (skb_queue_len(&offload->skb_queue) >
	    offload->skb_queue_len_max) {
		kfree_skb(skb);
		return -ENOBUFS;
	}

	skb_queue_tail(&offload->skb_queue, skb);
	can_rx_offload_schedule(offload);

	return 0;
}