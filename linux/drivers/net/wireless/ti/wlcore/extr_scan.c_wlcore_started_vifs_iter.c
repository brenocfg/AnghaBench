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
struct wl12xx_vif {int bss_type; TYPE_1__* wl; int /*<<< orphan*/  flags; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  active_sta_count; } ;

/* Variables and functions */
#define  BSS_TYPE_AP_BSS 129 
#define  BSS_TYPE_STA_BSS 128 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static void wlcore_started_vifs_iter(void *data, u8 *mac,
				     struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	bool active = false;
	int *count = (int *)data;

	/*
	 * count active interfaces according to interface type.
	 * checking only bss_conf.idle is bad for some cases, e.g.
	 * we don't want to count sta in p2p_find as active interface.
	 */
	switch (wlvif->bss_type) {
	case BSS_TYPE_STA_BSS:
		if (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags))
			active = true;
		break;

	case BSS_TYPE_AP_BSS:
		if (wlvif->wl->active_sta_count > 0)
			active = true;
		break;

	default:
		break;
	}

	if (active)
		(*count)++;
}