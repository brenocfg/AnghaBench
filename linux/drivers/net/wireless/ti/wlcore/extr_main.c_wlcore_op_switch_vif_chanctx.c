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
struct wl1271 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct ieee80211_vif_chanctx_switch {int /*<<< orphan*/  new_ctx; int /*<<< orphan*/  vif; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
typedef  enum ieee80211_chanctx_switch_mode { ____Placeholder_ieee80211_chanctx_switch_mode } ieee80211_chanctx_switch_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int __wlcore_switch_vif_chan (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int,int) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wlcore_op_switch_vif_chanctx(struct ieee80211_hw *hw,
			     struct ieee80211_vif_chanctx_switch *vifs,
			     int n_vifs,
			     enum ieee80211_chanctx_switch_mode mode)
{
	struct wl1271 *wl = hw->priv;
	int i, ret;

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 switch chanctx n_vifs %d mode %d",
		     n_vifs, mode);

	mutex_lock(&wl->mutex);

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	for (i = 0; i < n_vifs; i++) {
		struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vifs[i].vif);

		ret = __wlcore_switch_vif_chan(wl, wlvif, vifs[i].new_ctx);
		if (ret)
			goto out_sleep;
	}
out_sleep:
	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	return 0;
}