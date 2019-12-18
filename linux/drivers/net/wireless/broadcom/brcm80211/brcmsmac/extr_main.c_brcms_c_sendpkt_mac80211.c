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
typedef  int /*<<< orphan*/  uint ;
struct sk_buff {int dummy; } ;
struct scb {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct brcms_c_info {struct scb pri_scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_ac_to_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_d11hdrs_mac80211 (struct brcms_c_info*,struct ieee80211_hw*,struct sk_buff*,struct scb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_tx (struct brcms_c_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 

bool brcms_c_sendpkt_mac80211(struct brcms_c_info *wlc, struct sk_buff *sdu,
			      struct ieee80211_hw *hw)
{
	uint fifo;
	struct scb *scb = &wlc->pri_scb;

	fifo = brcms_ac_to_fifo(skb_get_queue_mapping(sdu));
	brcms_c_d11hdrs_mac80211(wlc, hw, sdu, scb, 0, 1, fifo, 0);
	if (!brcms_c_tx(wlc, sdu))
		return true;

	/* packet discarded */
	dev_kfree_skb_any(sdu);
	return false;
}