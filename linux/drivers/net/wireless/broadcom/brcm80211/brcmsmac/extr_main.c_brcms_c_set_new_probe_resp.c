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
struct brcms_c_info {struct sk_buff* probe_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11_PHY_HDR_LEN ; 
 int /*<<< orphan*/  brcms_c_update_probe_resp (struct brcms_c_info*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

void brcms_c_set_new_probe_resp(struct brcms_c_info *wlc,
				struct sk_buff *probe_resp)
{
	if (!probe_resp)
		return;
	if (wlc->probe_resp)
		dev_kfree_skb_any(wlc->probe_resp);
	wlc->probe_resp = probe_resp;

	/* add PLCP */
	skb_push(wlc->probe_resp, D11_PHY_HDR_LEN);
	brcms_c_update_probe_resp(wlc, false);
}