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
struct ieee80211_hw {int dummy; } ;
struct b43_wldev {int dummy; } ;
struct b43_wl {int radio_enabled; int /*<<< orphan*/  txpower_adjust_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  beacon_update_trigger; struct b43_wldev* current_dev; } ;

/* Variables and functions */
 scalar_t__ B43_STAT_STARTED ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wireless_core_exit (struct b43_wldev*) ; 
 struct b43_wldev* b43_wireless_core_stop (struct b43_wldev*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_op_stop(struct ieee80211_hw *hw)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev = wl->current_dev;

	cancel_work_sync(&(wl->beacon_update_trigger));

	if (!dev)
		goto out;

	mutex_lock(&wl->mutex);
	if (b43_status(dev) >= B43_STAT_STARTED) {
		dev = b43_wireless_core_stop(dev);
		if (!dev)
			goto out_unlock;
	}
	b43_wireless_core_exit(dev);
	wl->radio_enabled = false;

out_unlock:
	mutex_unlock(&wl->mutex);
out:
	cancel_work_sync(&(wl->txpower_adjust_work));
}