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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct can_rx_offload_cb {int /*<<< orphan*/  timestamp; } ;
struct can_rx_offload {scalar_t__ skb_queue_len_max; int (* mailbox_read ) (struct can_rx_offload*,struct can_frame*,int /*<<< orphan*/ *,unsigned int) ;TYPE_2__* dev; int /*<<< orphan*/  skb_queue; } ;
struct can_frame {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 struct sk_buff* alloc_can_skb (TYPE_2__*,struct can_frame**) ; 
 struct can_rx_offload_cb* can_rx_offload_get_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int stub1 (struct can_rx_offload*,struct can_frame*,int /*<<< orphan*/ *,unsigned int) ; 
 int stub2 (struct can_rx_offload*,struct can_frame*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static struct sk_buff *can_rx_offload_offload_one(struct can_rx_offload *offload, unsigned int n)
{
	struct sk_buff *skb = NULL;
	struct can_rx_offload_cb *cb;
	struct can_frame *cf;
	int ret;

	/* If queue is full or skb not available, read to discard mailbox */
	if (likely(skb_queue_len(&offload->skb_queue) <=
		   offload->skb_queue_len_max))
		skb = alloc_can_skb(offload->dev, &cf);

	if (!skb) {
		struct can_frame cf_overflow;
		u32 timestamp;

		ret = offload->mailbox_read(offload, &cf_overflow,
					    &timestamp, n);
		if (ret)
			offload->dev->stats.rx_dropped++;

		return NULL;
	}

	cb = can_rx_offload_get_cb(skb);
	ret = offload->mailbox_read(offload, cf, &cb->timestamp, n);
	if (!ret) {
		kfree_skb(skb);
		return NULL;
	}

	return skb;
}