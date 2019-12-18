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
struct wireless_dev {int /*<<< orphan*/  iftype; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {TYPE_1__* scan_request; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vif_mutex; struct wireless_dev* p2p_wdev; struct wireless_dev* radio_wdev; } ;
struct TYPE_2__ {struct wireless_dev* wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* wdev_to_vif (struct wil6210_priv*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wil_abort_scan (struct wil6210_vif*,int) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_p2p_stop_radio_operations (struct wil6210_priv*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static void wil_cfg80211_abort_scan(struct wiphy *wiphy,
				    struct wireless_dev *wdev)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = wdev_to_vif(wil, wdev);

	wil_dbg_misc(wil, "wdev=0x%p iftype=%d\n", wdev, wdev->iftype);

	mutex_lock(&wil->mutex);
	mutex_lock(&wil->vif_mutex);

	if (!vif->scan_request)
		goto out;

	if (wdev != vif->scan_request->wdev) {
		wil_dbg_misc(wil, "abort scan was called on the wrong iface\n");
		goto out;
	}

	if (wdev == wil->p2p_wdev && wil->radio_wdev == wil->p2p_wdev)
		wil_p2p_stop_radio_operations(wil);
	else
		wil_abort_scan(vif, true);

out:
	mutex_unlock(&wil->vif_mutex);
	mutex_unlock(&wil->mutex);
}