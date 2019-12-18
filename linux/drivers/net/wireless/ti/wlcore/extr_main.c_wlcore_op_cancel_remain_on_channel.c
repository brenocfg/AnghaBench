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
struct wl1271 {int /*<<< orphan*/  roc_complete_work; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_tx_flush (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_roc_completed (struct wl1271*) ; 

__attribute__((used)) static int wlcore_op_cancel_remain_on_channel(struct ieee80211_hw *hw,
					      struct ieee80211_vif *vif)
{
	struct wl1271 *wl = hw->priv;

	wl1271_debug(DEBUG_MAC80211, "mac80211 croc");

	/* TODO: per-vif */
	wl1271_tx_flush(wl);

	/*
	 * we can't just flush_work here, because it might deadlock
	 * (as we might get called from the same workqueue)
	 */
	cancel_delayed_work_sync(&wl->roc_complete_work);
	wlcore_roc_completed(wl);

	return 0;
}