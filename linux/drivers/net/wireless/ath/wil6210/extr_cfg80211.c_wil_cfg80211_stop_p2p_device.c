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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vif_mutex; scalar_t__ p2p_dev_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_p2p_stop_radio_operations (struct wil6210_priv*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static void wil_cfg80211_stop_p2p_device(struct wiphy *wiphy,
					 struct wireless_dev *wdev)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);

	if (!wil->p2p_dev_started)
		return;

	wil_dbg_misc(wil, "stop_p2p_device: entered\n");
	mutex_lock(&wil->mutex);
	mutex_lock(&wil->vif_mutex);
	wil_p2p_stop_radio_operations(wil);
	wil->p2p_dev_started = 0;
	mutex_unlock(&wil->vif_mutex);
	mutex_unlock(&wil->mutex);
}