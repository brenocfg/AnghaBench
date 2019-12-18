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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int wl1271_acx_beacon_filter_opt (struct wl1271*,struct wl12xx_vif*,int) ; 
 int wl1271_ap_init_deauth_template (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_ap_init_null_template (struct wl1271*,struct ieee80211_vif*) ; 
 int wl1271_ap_init_qos_null_template (struct wl1271*,struct ieee80211_vif*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

int wl1271_ap_init_templates(struct wl1271 *wl, struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	ret = wl1271_ap_init_deauth_template(wl, wlvif);
	if (ret < 0)
		return ret;

	ret = wl1271_ap_init_null_template(wl, vif);
	if (ret < 0)
		return ret;

	ret = wl1271_ap_init_qos_null_template(wl, vif);
	if (ret < 0)
		return ret;

	/*
	 * when operating as AP we want to receive external beacons for
	 * configuring ERP protection.
	 */
	ret = wl1271_acx_beacon_filter_opt(wl, wlvif, false);
	if (ret < 0)
		return ret;

	return 0;
}