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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wl1271 {int dummy; } ;
struct ieee80211_sta_ht_cap {int dummy; } ;

/* Variables and functions */
 int wl18xx_acx_set_peer_cap (struct wl1271*,struct ieee80211_sta_ht_cap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl18xx_set_peer_cap(struct wl1271 *wl,
			       struct ieee80211_sta_ht_cap *ht_cap,
			       bool allow_ht_operation,
			       u32 rate_set, u8 hlid)
{
	return wl18xx_acx_set_peer_cap(wl, ht_cap, allow_ht_operation,
				       rate_set, hlid);
}