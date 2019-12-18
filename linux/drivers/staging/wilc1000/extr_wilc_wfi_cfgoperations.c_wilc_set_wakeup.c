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
struct wiphy {int dummy; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wilc {int /*<<< orphan*/  vif_mutex; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct wilc_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 struct wilc_vif* wilc_get_wl_to_vif (struct wilc*) ; 
 struct wilc* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static void wilc_set_wakeup(struct wiphy *wiphy, bool enabled)
{
	struct wilc *wl = wiphy_priv(wiphy);
	struct wilc_vif *vif;

	mutex_lock(&wl->vif_mutex);
	vif = wilc_get_wl_to_vif(wl);
	if (IS_ERR(vif)) {
		mutex_unlock(&wl->vif_mutex);
		return;
	}

	netdev_info(vif->ndev, "cfg set wake up = %d\n", enabled);
	mutex_unlock(&wl->vif_mutex);
}