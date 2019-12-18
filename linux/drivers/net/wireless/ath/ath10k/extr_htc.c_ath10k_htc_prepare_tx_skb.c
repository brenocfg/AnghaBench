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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ath10k_htc_hdr {scalar_t__ seq_no; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  eid; } ;
struct ath10k_htc_ep {TYPE_1__* htc; int /*<<< orphan*/  seq_no; scalar_t__ tx_credit_flow_enabled; int /*<<< orphan*/  eid; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_HTC_FLAG_NEED_CREDIT_UPDATE ; 
 int /*<<< orphan*/  __cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ath10k_htc_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_htc_prepare_tx_skb(struct ath10k_htc_ep *ep,
				      struct sk_buff *skb)
{
	struct ath10k_htc_hdr *hdr;

	hdr = (struct ath10k_htc_hdr *)skb->data;
	memset(hdr, 0, sizeof(struct ath10k_htc_hdr));

	hdr->eid = ep->eid;
	hdr->len = __cpu_to_le16(skb->len - sizeof(*hdr));
	hdr->flags = 0;
	if (ep->tx_credit_flow_enabled)
		hdr->flags |= ATH10K_HTC_FLAG_NEED_CREDIT_UPDATE;

	spin_lock_bh(&ep->htc->tx_lock);
	hdr->seq_no = ep->seq_no++;
	spin_unlock_bh(&ep->htc->tx_lock);
}