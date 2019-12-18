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
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_wl {int beacon0_uploaded; int beacon1_uploaded; int beacon_templates_virgin; int radio_enabled; int /*<<< orphan*/  mutex; scalar_t__ filter_flags; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  bssid; struct b43legacy_wldev* current_dev; } ;

/* Variables and functions */
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 scalar_t__ B43legacy_STAT_STARTED ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_wireless_core_exit (struct b43legacy_wldev*) ; 
 int b43legacy_wireless_core_init (struct b43legacy_wldev*) ; 
 int b43legacy_wireless_core_start (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_start_polling (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b43legacy_op_start(struct ieee80211_hw *hw)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	struct b43legacy_wldev *dev = wl->current_dev;
	int did_init = 0;
	int err = 0;

	/* Kill all old instance specific information to make sure
	 * the card won't use it in the short timeframe between start
	 * and mac80211 reconfiguring it. */
	eth_zero_addr(wl->bssid);
	eth_zero_addr(wl->mac_addr);
	wl->filter_flags = 0;
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	wl->beacon_templates_virgin = true;
	wl->radio_enabled = true;

	mutex_lock(&wl->mutex);

	if (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED) {
		err = b43legacy_wireless_core_init(dev);
		if (err)
			goto out_mutex_unlock;
		did_init = 1;
	}

	if (b43legacy_status(dev) < B43legacy_STAT_STARTED) {
		err = b43legacy_wireless_core_start(dev);
		if (err) {
			if (did_init)
				b43legacy_wireless_core_exit(dev);
			goto out_mutex_unlock;
		}
	}

	wiphy_rfkill_start_polling(hw->wiphy);

out_mutex_unlock:
	mutex_unlock(&wl->mutex);

	return err;
}