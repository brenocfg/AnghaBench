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
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  basic_rate_set; int /*<<< orphan*/  basic_rate; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  WLVIF_FLAG_IN_USE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_acx_sta_rate_policies (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl1271_set_band_rate (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl1271_tx_min_rate_get (struct wl1271*,int /*<<< orphan*/ ) ; 
 int wl12xx_cmd_role_stop_sta (struct wl1271*,struct wl12xx_vif*) ; 

__attribute__((used)) static int wlcore_clear_bssid(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	/* revert back to minimum rates for the current band */
	wl1271_set_band_rate(wl, wlvif);
	wlvif->basic_rate = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);

	ret = wl1271_acx_sta_rate_policies(wl, wlvif);
	if (ret < 0)
		return ret;

	if (wlvif->bss_type == BSS_TYPE_STA_BSS &&
	    test_bit(WLVIF_FLAG_IN_USE, &wlvif->flags)) {
		ret = wl12xx_cmd_role_stop_sta(wl, wlvif);
		if (ret < 0)
			return ret;
	}

	clear_bit(WLVIF_FLAG_IN_USE, &wlvif->flags);
	return 0;
}