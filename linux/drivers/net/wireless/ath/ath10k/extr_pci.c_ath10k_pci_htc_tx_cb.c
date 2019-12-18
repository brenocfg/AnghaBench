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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ath10k_ce_pipe {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 scalar_t__ ath10k_ce_completed_send_next (struct ath10k_ce_pipe*,void**) ; 
 int /*<<< orphan*/  ath10k_htc_tx_completion_handler (struct ath10k*,struct sk_buff*) ; 

__attribute__((used)) static void ath10k_pci_htc_tx_cb(struct ath10k_ce_pipe *ce_state)
{
	struct ath10k *ar = ce_state->ar;
	struct sk_buff_head list;
	struct sk_buff *skb;

	__skb_queue_head_init(&list);
	while (ath10k_ce_completed_send_next(ce_state, (void **)&skb) == 0) {
		/* no need to call tx completion for NULL pointers */
		if (skb == NULL)
			continue;

		__skb_queue_tail(&list, skb);
	}

	while ((skb = __skb_dequeue(&list)))
		ath10k_htc_tx_completion_handler(ar, skb);
}