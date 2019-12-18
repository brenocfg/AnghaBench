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
typedef  size_t u8 ;
typedef  int u32 ;
struct wl1271_station {size_t hlid; } ;
struct wl1271 {TYPE_1__* links; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct TYPE_2__ {int fw_rate_mbps; } ;

/* Variables and functions */

__attribute__((used)) static u32 wlcore_op_get_expected_throughput(struct ieee80211_hw *hw,
					     struct ieee80211_sta *sta)
{
	struct wl1271_station *wl_sta = (struct wl1271_station *)sta->drv_priv;
	struct wl1271 *wl = hw->priv;
	u8 hlid = wl_sta->hlid;

	/* return in units of Kbps */
	return (wl->links[hlid].fw_rate_mbps * 1000);
}