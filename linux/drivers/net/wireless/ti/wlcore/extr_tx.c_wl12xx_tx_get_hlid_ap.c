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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  global_hlid; int /*<<< orphan*/  bcast_hlid; } ;
struct wl12xx_vif {TYPE_1__ ap; int /*<<< orphan*/  flags; } ;
struct wl1271_station {int /*<<< orphan*/  hlid; } ;
struct wl1271 {int /*<<< orphan*/  system_hlid; } ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLVIF_FLAG_AP_STARTED ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 wl12xx_tx_get_hlid_ap(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				struct sk_buff *skb, struct ieee80211_sta *sta)
{
	if (sta) {
		struct wl1271_station *wl_sta;

		wl_sta = (struct wl1271_station *)sta->drv_priv;
		return wl_sta->hlid;
	} else {
		struct ieee80211_hdr *hdr;

		if (!test_bit(WLVIF_FLAG_AP_STARTED, &wlvif->flags))
			return wl->system_hlid;

		hdr = (struct ieee80211_hdr *)skb->data;
		if (is_multicast_ether_addr(ieee80211_get_DA(hdr)))
			return wlvif->ap.bcast_hlid;
		else
			return wlvif->ap.global_hlid;
	}
}