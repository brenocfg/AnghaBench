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
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_wl {int radio_enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  beacon_update_trigger; struct b43legacy_wldev* current_dev; } ;

/* Variables and functions */
 scalar_t__ B43legacy_STAT_STARTED ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_wireless_core_exit (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_wireless_core_stop (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43legacy_op_stop(struct ieee80211_hw *hw)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	struct b43legacy_wldev *dev = wl->current_dev;

	cancel_work_sync(&(wl->beacon_update_trigger));

	mutex_lock(&wl->mutex);
	if (b43legacy_status(dev) >= B43legacy_STAT_STARTED)
		b43legacy_wireless_core_stop(dev);
	b43legacy_wireless_core_exit(dev);
	wl->radio_enabled = false;
	mutex_unlock(&wl->mutex);
}