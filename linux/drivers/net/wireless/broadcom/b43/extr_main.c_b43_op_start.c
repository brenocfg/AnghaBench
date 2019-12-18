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
struct b43_wldev {int dummy; } ;
struct b43_wl {int radiotap_enabled; int beacon0_uploaded; int beacon1_uploaded; int beacon_templates_virgin; int radio_enabled; int /*<<< orphan*/  mutex; scalar_t__ filter_flags; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  bssid; struct b43_wldev* current_dev; } ;

/* Variables and functions */
 scalar_t__ B43_STAT_INITIALIZED ; 
 scalar_t__ B43_STAT_STARTED ; 
 int /*<<< orphan*/  b43_op_config (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_qos_clear (struct b43_wl*) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wireless_core_exit (struct b43_wldev*) ; 
 int b43_wireless_core_init (struct b43_wldev*) ; 
 int b43_wireless_core_start (struct b43_wldev*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_start_polling (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b43_op_start(struct ieee80211_hw *hw)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev = wl->current_dev;
	int did_init = 0;
	int err = 0;

	/* Kill all old instance specific information to make sure
	 * the card won't use it in the short timeframe between start
	 * and mac80211 reconfiguring it. */
	eth_zero_addr(wl->bssid);
	eth_zero_addr(wl->mac_addr);
	wl->filter_flags = 0;
	wl->radiotap_enabled = false;
	b43_qos_clear(wl);
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	wl->beacon_templates_virgin = true;
	wl->radio_enabled = true;

	mutex_lock(&wl->mutex);

	if (b43_status(dev) < B43_STAT_INITIALIZED) {
		err = b43_wireless_core_init(dev);
		if (err)
			goto out_mutex_unlock;
		did_init = 1;
	}

	if (b43_status(dev) < B43_STAT_STARTED) {
		err = b43_wireless_core_start(dev);
		if (err) {
			if (did_init)
				b43_wireless_core_exit(dev);
			goto out_mutex_unlock;
		}
	}

	/* XXX: only do if device doesn't support rfkill irq */
	wiphy_rfkill_start_polling(hw->wiphy);

 out_mutex_unlock:
	mutex_unlock(&wl->mutex);

	/*
	 * Configuration may have been overwritten during initialization.
	 * Reload the configuration, but only if initialization was
	 * successful. Reloading the configuration after a failed init
	 * may hang the system.
	 */
	if (!err)
		b43_op_config(hw, ~0);

	return err;
}