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
struct TYPE_3__ {int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 struct sk_buff* alloc_can_skb (TYPE_2__*,struct can_frame**) ; 
 struct can_rx_offload_cb* can_rx_offload_get_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int stub1 (struct can_rx_offload*,struct can_frame*,int /*<<< orphan*/ *,unsigned int) ; 
 int stub2 (struct can_rx_offload*,struct can_frame*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *
can_rx_offload_offload_one(struct can_rx_offload *offload, unsigned int n)
{
	struct sk_buff *skb = NULL, *skb_error = NULL;
	struct can_rx_offload_cb *cb;
	struct can_frame *cf;
	int ret;

	if (likely(skb_queue_len(&offload->skb_queue) <
		   offload->skb_queue_len_max)) {
		skb = alloc_can_skb(offload->dev, &cf);
		if (unlikely(!skb))
			skb_error = ERR_PTR(-ENOMEM);	/* skb alloc failed */
	} else {
		skb_error = ERR_PTR(-ENOBUFS);		/* skb_queue is full */
	}

	/* If queue is full or skb not available, drop by reading into
	 * overflow buffer.
	 */
	if (unlikely(skb_error)) {
		struct can_frame cf_overflow;
		u32 timestamp;

		ret = offload->mailbox_read(offload, &cf_overflow,
					    &timestamp, n);

		/* Mailbox was empty. */
		if (unlikely(!ret))
			return NULL;

		/* Mailbox has been read and we're dropping it or
		 * there was a problem reading the mailbox.
		 *
		 * Increment error counters in any case.
		 */
		offload->dev->stats.rx_dropped++;
		offload->dev->stats.rx_fifo_errors++;

		/* There was a problem reading the mailbox, propagate
		 * error value.
		 */
		if (unlikely(ret < 0))
			return ERR_PTR(ret);

		return skb_error;
	}

	cb = can_rx_offload_get_cb(skb);
	ret = offload->mailbox_read(offload, cf, &cb->timestamp, n);

	/* Mailbox was empty. */
	if (unlikely(!ret)) {
		kfree_skb(skb);
		return NULL;
	}

	/* There was a problem reading the mailbox, propagate error value. */
	if (unlikely(ret < 0)) {
		kfree_skb(skb);

		offload->dev->stats.rx_dropped++;
		offload->dev->stats.rx_fifo_errors++;

		return ERR_PTR(ret);
	}

	/* Mailbox was read. */
	return skb;
}