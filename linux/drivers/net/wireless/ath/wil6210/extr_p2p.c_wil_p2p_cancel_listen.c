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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct wil_p2p_info {scalar_t__ cookie; int /*<<< orphan*/  listen_chan; } ;
struct wil6210_vif {scalar_t__ mid; struct wil_p2p_info p2p; } ;
struct wil6210_priv {int /*<<< orphan*/  vif_mutex; TYPE_1__* main_ndev; int /*<<< orphan*/  radio_wdev; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  ieee80211_ptr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vif_to_radio_wdev (struct wil6210_priv*,struct wil6210_vif*) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wil_p2p_stop_discovery (struct wil6210_vif*) ; 

int wil_p2p_cancel_listen(struct wil6210_vif *vif, u64 cookie)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wil_p2p_info *p2p = &vif->p2p;
	u8 started;

	mutex_lock(&wil->mutex);

	if (cookie != p2p->cookie) {
		wil_info(wil, "Cookie mismatch: 0x%016llx vs. 0x%016llx\n",
			 p2p->cookie, cookie);
		mutex_unlock(&wil->mutex);
		return -ENOENT;
	}

	started = wil_p2p_stop_discovery(vif);

	mutex_unlock(&wil->mutex);

	if (!started) {
		wil_err(wil, "listen not started\n");
		return -ENOENT;
	}

	mutex_lock(&wil->vif_mutex);
	cfg80211_remain_on_channel_expired(vif_to_radio_wdev(wil, vif),
					   p2p->cookie,
					   &p2p->listen_chan,
					   GFP_KERNEL);
	if (vif->mid == 0)
		wil->radio_wdev = wil->main_ndev->ieee80211_ptr;
	mutex_unlock(&wil->vif_mutex);
	return 0;
}