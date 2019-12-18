#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wl1251 {int monitor_present; scalar_t__ default_key; int /*<<< orphan*/  joined; int /*<<< orphan*/ * vif; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* hw_key; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct TYPE_3__ {scalar_t__ hw_key_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  enable_tx_for_packet_injection (struct wl1251*) ; 
 scalar_t__ unlikely (int) ; 
 int wl1251_acx_default_key (struct wl1251*,scalar_t__) ; 
 int wl1251_tx_fill_hdr (struct wl1251*,struct sk_buff*,struct ieee80211_tx_info*) ; 
 int wl1251_tx_path_status (struct wl1251*) ; 
 int wl1251_tx_send_packet (struct wl1251*,struct sk_buff*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  wl1251_tx_trigger (struct wl1251*) ; 

__attribute__((used)) static int wl1251_tx_frame(struct wl1251 *wl, struct sk_buff *skb)
{
	struct ieee80211_tx_info *info;
	int ret = 0;
	u8 idx;

	info = IEEE80211_SKB_CB(skb);

	if (info->control.hw_key) {
		if (unlikely(wl->monitor_present))
			return -EINVAL;

		idx = info->control.hw_key->hw_key_idx;
		if (unlikely(wl->default_key != idx)) {
			ret = wl1251_acx_default_key(wl, idx);
			if (ret < 0)
				return ret;
		}
	}

	/* Enable tx path in monitor mode for packet injection */
	if ((wl->vif == NULL) && !wl->joined)
		enable_tx_for_packet_injection(wl);

	ret = wl1251_tx_path_status(wl);
	if (ret < 0)
		return ret;

	ret = wl1251_tx_fill_hdr(wl, skb, info);
	if (ret < 0)
		return ret;

	ret = wl1251_tx_send_packet(wl, skb, info);
	if (ret < 0)
		return ret;

	wl1251_tx_trigger(wl);

	return ret;
}