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
struct wireless_dev {int dummy; } ;
struct wil6210_priv {int /*<<< orphan*/  vif_mutex; TYPE_1__* main_ndev; int /*<<< orphan*/  radio_wdev; struct wireless_dev* p2p_wdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ieee80211_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_unregister_wdev (struct wireless_dev*) ; 
 int /*<<< orphan*/  kfree (struct wireless_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void wil_p2p_wdev_free(struct wil6210_priv *wil)
{
	struct wireless_dev *p2p_wdev;

	mutex_lock(&wil->vif_mutex);
	p2p_wdev = wil->p2p_wdev;
	wil->p2p_wdev = NULL;
	wil->radio_wdev = wil->main_ndev->ieee80211_ptr;
	mutex_unlock(&wil->vif_mutex);
	if (p2p_wdev) {
		cfg80211_unregister_wdev(p2p_wdev);
		kfree(p2p_wdev);
	}
}