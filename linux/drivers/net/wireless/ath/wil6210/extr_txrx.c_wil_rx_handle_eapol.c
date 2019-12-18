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
struct wireless_dev {scalar_t__ iftype; } ;
struct wil6210_vif {scalar_t__ ptk_rekey_state; } ;
struct wil6210_priv {int /*<<< orphan*/  fw_capabilities; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WIL_REKEY_IDLE ; 
 scalar_t__ WIL_REKEY_M3_RECEIVED ; 
 int /*<<< orphan*/  WMI_FW_CAPABILITY_SPLIT_REKEY ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wireless_dev* vif_to_wdev (struct wil6210_vif*) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_skb_is_eap_3 (struct wil6210_priv*,struct sk_buff*) ; 

__attribute__((used)) static void wil_rx_handle_eapol(struct wil6210_vif *vif, struct sk_buff *skb)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wireless_dev *wdev = vif_to_wdev(vif);

	if (wdev->iftype != NL80211_IFTYPE_STATION ||
	    !test_bit(WMI_FW_CAPABILITY_SPLIT_REKEY, wil->fw_capabilities))
		return;

	/* check if skb is a EAP message 3/4 */
	if (!wil_skb_is_eap_3(wil, skb))
		return;

	if (vif->ptk_rekey_state == WIL_REKEY_IDLE)
		vif->ptk_rekey_state = WIL_REKEY_M3_RECEIVED;
}