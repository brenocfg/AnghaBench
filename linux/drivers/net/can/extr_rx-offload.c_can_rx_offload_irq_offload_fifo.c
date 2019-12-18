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
struct can_rx_offload {int /*<<< orphan*/  skb_queue; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 struct sk_buff* can_rx_offload_offload_one (struct can_rx_offload*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_rx_offload_schedule (struct can_rx_offload*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int can_rx_offload_irq_offload_fifo(struct can_rx_offload *offload)
{
	struct sk_buff *skb;
	int received = 0;

	while (1) {
		skb = can_rx_offload_offload_one(offload, 0);
		if (IS_ERR(skb))
			continue;
		if (!skb)
			break;

		skb_queue_tail(&offload->skb_queue, skb);
		received++;
	}

	if (received)
		can_rx_offload_schedule(offload);

	return received;
}