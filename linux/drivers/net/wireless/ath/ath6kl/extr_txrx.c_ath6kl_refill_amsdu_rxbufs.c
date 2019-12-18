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
struct sk_buff {scalar_t__ data; scalar_t__ head; } ;
struct htc_packet {int /*<<< orphan*/  list; struct sk_buff* skb; } ;
struct ath6kl {int /*<<< orphan*/  lock; int /*<<< orphan*/  amsdu_rx_buffer_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_AMSDU_BUFFER_SIZE ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 scalar_t__ PTR_ALIGN (scalar_t__,int) ; 
 struct sk_buff* ath6kl_buf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_htc_rxpkt_info (struct htc_packet*,struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath6kl_refill_amsdu_rxbufs(struct ath6kl *ar, int count)
{
	struct htc_packet *packet;
	struct sk_buff *skb;

	while (count) {
		skb = ath6kl_buf_alloc(ATH6KL_AMSDU_BUFFER_SIZE);
		if (!skb)
			return;

		packet = (struct htc_packet *) skb->head;
		if (!IS_ALIGNED((unsigned long) skb->data, 4)) {
			size_t len = skb_headlen(skb);
			skb->data = PTR_ALIGN(skb->data - 4, 4);
			skb_set_tail_pointer(skb, len);
		}
		set_htc_rxpkt_info(packet, skb, skb->data,
				   ATH6KL_AMSDU_BUFFER_SIZE, 0);
		packet->skb = skb;

		spin_lock_bh(&ar->lock);
		list_add_tail(&packet->list, &ar->amsdu_rx_buffer_queue);
		spin_unlock_bh(&ar->lock);
		count--;
	}
}