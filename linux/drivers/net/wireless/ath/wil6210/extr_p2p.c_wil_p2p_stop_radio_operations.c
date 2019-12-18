#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wil_p2p_info {int /*<<< orphan*/  listen_chan; int /*<<< orphan*/  cookie; int /*<<< orphan*/  discovery_started; } ;
struct wil6210_vif {TYPE_2__* scan_request; struct wil_p2p_info p2p; } ;
struct wil6210_priv {scalar_t__ radio_wdev; scalar_t__ p2p_wdev; TYPE_1__* main_ndev; int /*<<< orphan*/  vif_mutex; int /*<<< orphan*/  mutex; } ;
struct cfg80211_scan_info {int aborted; } ;
struct TYPE_4__ {scalar_t__ wdev; } ;
struct TYPE_3__ {scalar_t__ ieee80211_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_scan_done (TYPE_2__*,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* ndev_to_vif (TYPE_1__*) ; 
 int /*<<< orphan*/  wil_abort_scan (struct wil6210_vif*,int) ; 
 int /*<<< orphan*/  wil_p2p_stop_discovery (struct wil6210_vif*) ; 

void wil_p2p_stop_radio_operations(struct wil6210_priv *wil)
{
	struct wil6210_vif *vif = ndev_to_vif(wil->main_ndev);
	struct wil_p2p_info *p2p = &vif->p2p;
	struct cfg80211_scan_info info = {
		.aborted = true,
	};

	lockdep_assert_held(&wil->mutex);
	lockdep_assert_held(&wil->vif_mutex);

	if (wil->radio_wdev != wil->p2p_wdev)
		goto out;

	if (!p2p->discovery_started) {
		/* Regular scan on the p2p device */
		if (vif->scan_request &&
		    vif->scan_request->wdev == wil->p2p_wdev)
			wil_abort_scan(vif, true);
		goto out;
	}

	/* Search or listen on p2p device */
	mutex_unlock(&wil->vif_mutex);
	wil_p2p_stop_discovery(vif);
	mutex_lock(&wil->vif_mutex);

	if (vif->scan_request) {
		/* search */
		cfg80211_scan_done(vif->scan_request, &info);
		vif->scan_request = NULL;
	} else {
		/* listen */
		cfg80211_remain_on_channel_expired(wil->radio_wdev,
						   p2p->cookie,
						   &p2p->listen_chan,
						   GFP_KERNEL);
	}

out:
	wil->radio_wdev = wil->main_ndev->ieee80211_ptr;
}