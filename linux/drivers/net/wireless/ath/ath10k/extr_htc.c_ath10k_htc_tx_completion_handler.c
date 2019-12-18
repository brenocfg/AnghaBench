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
struct ath10k_skb_cb {size_t eid; } ;
struct ath10k_htc_ep {int dummy; } ;
struct ath10k_htc {struct ath10k_htc_ep* endpoint; } ;
struct ath10k {struct ath10k_htc htc; } ;

/* Variables and functions */
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath10k_htc_notify_tx_completion (struct ath10k_htc_ep*,struct sk_buff*) ; 

void ath10k_htc_tx_completion_handler(struct ath10k *ar, struct sk_buff *skb)
{
	struct ath10k_htc *htc = &ar->htc;
	struct ath10k_skb_cb *skb_cb;
	struct ath10k_htc_ep *ep;

	if (WARN_ON_ONCE(!skb))
		return;

	skb_cb = ATH10K_SKB_CB(skb);
	ep = &htc->endpoint[skb_cb->eid];

	ath10k_htc_notify_tx_completion(ep, skb);
	/* the skb now belongs to the completion handler */
}