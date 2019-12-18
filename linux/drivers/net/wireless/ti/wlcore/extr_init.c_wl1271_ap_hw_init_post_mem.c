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
struct wl1271 {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int wl1271_ap_init_templates (struct wl1271*,struct ieee80211_vif*) ; 

__attribute__((used)) static int wl1271_ap_hw_init_post_mem(struct wl1271 *wl,
				      struct ieee80211_vif *vif)
{
	return wl1271_ap_init_templates(wl, vif);
}