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
typedef  scalar_t__ u8 ;
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WL12XX_INVALID_LINK_ID ; 
 struct ieee80211_sta* ieee80211_find_sta (struct ieee80211_vif*,scalar_t__ const*) ; 
 scalar_t__ is_zero_ether_addr (scalar_t__ const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wlcore_save_freed_pkts (struct wl1271*,struct wl12xx_vif*,scalar_t__,struct ieee80211_sta*) ; 

__attribute__((used)) static void wlcore_save_freed_pkts_addr(struct wl1271 *wl,
					struct wl12xx_vif *wlvif,
					u8 hlid, const u8 *addr)
{
	struct ieee80211_sta *sta;
	struct ieee80211_vif *vif = wl12xx_wlvif_to_vif(wlvif);

	if (WARN_ON(hlid == WL12XX_INVALID_LINK_ID ||
		    is_zero_ether_addr(addr)))
		return;

	rcu_read_lock();
	sta = ieee80211_find_sta(vif, addr);
	if (sta)
		wlcore_save_freed_pkts(wl, wlvif, hlid, sta);
	rcu_read_unlock();
}