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
struct sk_buff {scalar_t__ data; } ;
struct ath10k_htc_hdr {size_t eid; } ;
struct ath10k_htc_ep {int dummy; } ;
struct TYPE_2__ {struct ath10k_htc_ep* endpoint; } ;
struct ath10k {TYPE_1__ htc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_htc_notify_tx_completion (struct ath10k_htc_ep*,struct sk_buff*) ; 

__attribute__((used)) static void ath10k_usb_tx_complete(struct ath10k *ar, struct sk_buff *skb)
{
	struct ath10k_htc_hdr *htc_hdr;
	struct ath10k_htc_ep *ep;

	htc_hdr = (struct ath10k_htc_hdr *)skb->data;
	ep = &ar->htc.endpoint[htc_hdr->eid];
	ath10k_htc_notify_tx_completion(ep, skb);
	/* The TX complete handler now owns the skb... */
}