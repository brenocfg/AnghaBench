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
struct wl12xx_vif {int /*<<< orphan*/  pending_auth_complete_work; int /*<<< orphan*/  pending_auth_reply_time; } ;
struct wl1271_tx_hw_descr {int dummy; } ;
struct wl1271 {int /*<<< orphan*/  hw; } ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLCORE_PEND_AUTH_ROC_TIMEOUT ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_acx_set_inconnection_sta (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_update_inconn_sta (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void wl1271_tx_ap_update_inconnection_sta(struct wl1271 *wl,
						 struct wl12xx_vif *wlvif,
						 struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr;

	hdr = (struct ieee80211_hdr *)(skb->data +
				       sizeof(struct wl1271_tx_hw_descr));
	if (!ieee80211_is_auth(hdr->frame_control))
		return;

	/*
	 * add the station to the known list before transmitting the
	 * authentication response. this way it won't get de-authed by FW
	 * when transmitting too soon.
	 */
	wl1271_acx_set_inconnection_sta(wl, wlvif, hdr->addr1);

	/*
	 * ROC for 1 second on the AP channel for completing the connection.
	 * Note the ROC will be continued by the update_sta_state callbacks
	 * once the station reaches the associated state.
	 */
	wlcore_update_inconn_sta(wl, wlvif, NULL, true);
	wlvif->pending_auth_reply_time = jiffies;
	cancel_delayed_work(&wlvif->pending_auth_complete_work);
	ieee80211_queue_delayed_work(wl->hw,
				&wlvif->pending_auth_complete_work,
				msecs_to_jiffies(WLCORE_PEND_AUTH_ROC_TIMEOUT));
}