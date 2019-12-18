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
struct wl12xx_vif {int /*<<< orphan*/  channel_switch_work; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  flags; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct ieee80211_channel_switch {unsigned long count; } ;
struct TYPE_2__ {int (* channel_switch ) (struct wl1271*,struct wl12xx_vif*,struct ieee80211_channel_switch*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 scalar_t__ WLCORE_STATE_OFF ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  WLVIF_FLAG_CS_PROGRESS ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (struct ieee80211_vif*,int) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned long ieee80211_tu_to_usec (int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct wl1271*,struct wl12xx_vif*,struct ieee80211_channel_switch*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_tx_flush (struct wl1271*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static void wl12xx_op_channel_switch(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif,
				     struct ieee80211_channel_switch *ch_switch)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 channel switch");

	wl1271_tx_flush(wl);

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state == WLCORE_STATE_OFF)) {
		if (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags))
			ieee80211_chswitch_done(vif, false);
		goto out;
	} else if (unlikely(wl->state != WLCORE_STATE_ON)) {
		goto out;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	/* TODO: change mac80211 to pass vif as param */

	if (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags)) {
		unsigned long delay_usec;

		ret = wl->ops->channel_switch(wl, wlvif, ch_switch);
		if (ret)
			goto out_sleep;

		set_bit(WLVIF_FLAG_CS_PROGRESS, &wlvif->flags);

		/* indicate failure 5 seconds after channel switch time */
		delay_usec = ieee80211_tu_to_usec(wlvif->beacon_int) *
			ch_switch->count;
		ieee80211_queue_delayed_work(hw, &wlvif->channel_switch_work,
					     usecs_to_jiffies(delay_usec) +
					     msecs_to_jiffies(5000));
	}

out_sleep:
	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
}