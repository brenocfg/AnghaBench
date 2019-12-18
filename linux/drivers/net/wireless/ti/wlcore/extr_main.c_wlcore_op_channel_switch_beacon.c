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
struct wl12xx_vif {int /*<<< orphan*/  flags; int /*<<< orphan*/  role_id; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct cfg80211_chan_def {int dummy; } ;
struct ieee80211_channel_switch {int block_tx; int /*<<< orphan*/  count; struct cfg80211_chan_def chandef; } ;
struct TYPE_2__ {int (* channel_switch ) (struct wl1271*,struct wl12xx_vif*,struct ieee80211_channel_switch*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int EBUSY ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  WLVIF_FLAG_CS_PROGRESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct wl1271*,struct wl12xx_vif*,struct ieee80211_channel_switch*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 
 int wlcore_get_csa_count (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wlcore_op_channel_switch_beacon(struct ieee80211_hw *hw,
					    struct ieee80211_vif *vif,
					    struct cfg80211_chan_def *chandef)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct ieee80211_channel_switch ch_switch = {
		.block_tx = true,
		.chandef = *chandef,
	};
	int ret;

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 channel switch beacon (role %d)",
		     wlvif->role_id);

	ret = wlcore_get_csa_count(wl, wlvif, &ch_switch.count);
	if (ret < 0) {
		wl1271_error("error getting beacon (for CSA counter)");
		return;
	}

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EBUSY;
		goto out;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	ret = wl->ops->channel_switch(wl, wlvif, &ch_switch);
	if (ret)
		goto out_sleep;

	set_bit(WLVIF_FLAG_CS_PROGRESS, &wlvif->flags);

out_sleep:
	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
}