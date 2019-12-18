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
typedef  void* u16 ;
struct sk_buff {int dummy; } ;
struct brcms_c_info {void* beacon_dtim_period; void* beacon_tim_offset; struct sk_buff* beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11_PHY_HDR_LEN ; 
 int /*<<< orphan*/  brcms_c_update_beacon (struct brcms_c_info*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

void brcms_c_set_new_beacon(struct brcms_c_info *wlc, struct sk_buff *beacon,
			    u16 tim_offset, u16 dtim_period)
{
	if (!beacon)
		return;
	if (wlc->beacon)
		dev_kfree_skb_any(wlc->beacon);
	wlc->beacon = beacon;

	/* add PLCP */
	skb_push(wlc->beacon, D11_PHY_HDR_LEN);
	wlc->beacon_tim_offset = tim_offset;
	wlc->beacon_dtim_period = dtim_period;
	brcms_c_update_beacon(wlc);
}