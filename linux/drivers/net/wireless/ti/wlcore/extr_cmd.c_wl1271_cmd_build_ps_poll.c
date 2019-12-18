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
typedef  int /*<<< orphan*/  u16 ;
struct wl12xx_vif {int /*<<< orphan*/  basic_rate_set; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int /*<<< orphan*/  hw; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEMPL_PS_POLL ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_pspoll_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int wl1271_cmd_template_set (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 

int wl1271_cmd_build_ps_poll(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			     u16 aid)
{
	struct ieee80211_vif *vif = wl12xx_wlvif_to_vif(wlvif);
	struct sk_buff *skb;
	int ret = 0;

	skb = ieee80211_pspoll_get(wl->hw, vif);
	if (!skb)
		goto out;

	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_PS_POLL, skb->data,
				      skb->len, 0, wlvif->basic_rate_set);

out:
	dev_kfree_skb(skb);
	return ret;
}