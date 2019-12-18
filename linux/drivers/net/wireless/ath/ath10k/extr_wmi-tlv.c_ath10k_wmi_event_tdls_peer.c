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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_tlv_tdls_peer_event {int /*<<< orphan*/  vdev_id; TYPE_1__ peer_macaddr; int /*<<< orphan*/  peer_reason; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ath10k_vif {int /*<<< orphan*/  vif; } ;
struct ath10k {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void const**) ; 
 int /*<<< orphan*/  NL80211_TDLS_TEARDOWN ; 
 int /*<<< orphan*/  WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE ; 
#define  WMI_TDLS_TEARDOWN_REASON_PTR_TIMEOUT 130 
#define  WMI_TDLS_TEARDOWN_REASON_RSSI 129 
#define  WMI_TDLS_TEARDOWN_REASON_TX 128 
 size_t WMI_TLV_TAG_STRUCT_TDLS_PEER_EVENT ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ath10k_vif* ath10k_get_arvif (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 void** ath10k_wmi_tlv_parse_alloc (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* ieee80211_find_sta_by_ifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_tdls_oper_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void const**) ; 

__attribute__((used)) static void ath10k_wmi_event_tdls_peer(struct ath10k *ar, struct sk_buff *skb)
{
	struct ieee80211_sta *station;
	const struct wmi_tlv_tdls_peer_event *ev;
	const void **tb;
	struct ath10k_vif *arvif;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ath10k_warn(ar, "tdls peer failed to parse tlv");
		return;
	}
	ev = tb[WMI_TLV_TAG_STRUCT_TDLS_PEER_EVENT];
	if (!ev) {
		kfree(tb);
		ath10k_warn(ar, "tdls peer NULL event");
		return;
	}

	switch (__le32_to_cpu(ev->peer_reason)) {
	case WMI_TDLS_TEARDOWN_REASON_TX:
	case WMI_TDLS_TEARDOWN_REASON_RSSI:
	case WMI_TDLS_TEARDOWN_REASON_PTR_TIMEOUT:
		station = ieee80211_find_sta_by_ifaddr(ar->hw,
						       ev->peer_macaddr.addr,
						       NULL);
		if (!station) {
			ath10k_warn(ar, "did not find station from tdls peer event");
			kfree(tb);
			return;
		}
		arvif = ath10k_get_arvif(ar, __le32_to_cpu(ev->vdev_id));
		ieee80211_tdls_oper_request(
					arvif->vif, station->addr,
					NL80211_TDLS_TEARDOWN,
					WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE,
					GFP_ATOMIC
					);
		break;
	}
	kfree(tb);
}