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
struct wiphy {int dummy; } ;
struct wilc {int suspend_event; } ;
struct cfg80211_wowlan {int dummy; } ;

/* Variables and functions */
 scalar_t__ wilc_wlan_get_num_conn_ifcs (struct wilc*) ; 
 struct wilc* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int wilc_suspend(struct wiphy *wiphy, struct cfg80211_wowlan *wow)
{
	struct wilc *wl = wiphy_priv(wiphy);

	if (!wow && wilc_wlan_get_num_conn_ifcs(wl))
		wl->suspend_event = true;
	else
		wl->suspend_event = false;

	return 0;
}