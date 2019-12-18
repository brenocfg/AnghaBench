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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_msdus_q; } ;
struct ath10k {TYPE_1__ htt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_process_rx (struct ath10k*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_htt_rx_deliver_msdu(struct ath10k *ar, int quota, int budget)
{
	struct sk_buff *skb;

	while (quota < budget) {
		if (skb_queue_empty(&ar->htt.rx_msdus_q))
			break;

		skb = skb_dequeue(&ar->htt.rx_msdus_q);
		if (!skb)
			break;
		ath10k_process_rx(ar, skb);
		quota++;
	}

	return quota;
}