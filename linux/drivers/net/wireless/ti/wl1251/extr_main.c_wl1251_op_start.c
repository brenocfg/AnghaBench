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
struct wl1251 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  chip_id; } ;
struct wiphy {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  hw_version; } ;
struct ieee80211_hw {struct wiphy* wiphy; struct wl1251* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int EBUSY ; 
 scalar_t__ WL1251_STATE_OFF ; 
 scalar_t__ WL1251_STATE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wl1251_acx_station_id (struct wl1251*) ; 
 int wl1251_boot (struct wl1251*) ; 
 int wl1251_chip_wakeup (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_error (char*,scalar_t__) ; 
 int wl1251_hw_init (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_power_off (struct wl1251*) ; 

__attribute__((used)) static int wl1251_op_start(struct ieee80211_hw *hw)
{
	struct wl1251 *wl = hw->priv;
	struct wiphy *wiphy = hw->wiphy;
	int ret = 0;

	wl1251_debug(DEBUG_MAC80211, "mac80211 start");

	mutex_lock(&wl->mutex);

	if (wl->state != WL1251_STATE_OFF) {
		wl1251_error("cannot start because not in off state: %d",
			     wl->state);
		ret = -EBUSY;
		goto out;
	}

	ret = wl1251_chip_wakeup(wl);
	if (ret < 0)
		goto out;

	ret = wl1251_boot(wl);
	if (ret < 0)
		goto out;

	ret = wl1251_hw_init(wl);
	if (ret < 0)
		goto out;

	ret = wl1251_acx_station_id(wl);
	if (ret < 0)
		goto out;

	wl->state = WL1251_STATE_ON;

	wl1251_info("firmware booted (%s)", wl->fw_ver);

	/* update hw/fw version info in wiphy struct */
	wiphy->hw_version = wl->chip_id;
	strncpy(wiphy->fw_version, wl->fw_ver, sizeof(wiphy->fw_version));

out:
	if (ret < 0)
		wl1251_power_off(wl);

	mutex_unlock(&wl->mutex);

	return ret;
}