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
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct wilc_vif {int idx; int /*<<< orphan*/  iftype; scalar_t__ monitor_flag; int /*<<< orphan*/  ndev; } ;
struct wilc {int vif_num; int /*<<< orphan*/  vif_mutex; struct wilc_vif** vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  cfg80211_stop_iface (struct wiphy*,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_get_vif_idx (struct wilc_vif*) ; 
 int /*<<< orphan*/  wilc_set_operation_mode (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wilc_wfi_deinit_mon_interface (struct wilc*,int) ; 
 struct wilc* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int del_virtual_intf(struct wiphy *wiphy, struct wireless_dev *wdev)
{
	struct wilc *wl = wiphy_priv(wiphy);
	struct wilc_vif *vif;
	int i;

	if (wdev->iftype == NL80211_IFTYPE_AP ||
	    wdev->iftype == NL80211_IFTYPE_P2P_GO)
		wilc_wfi_deinit_mon_interface(wl, true);
	vif = netdev_priv(wdev->netdev);
	cfg80211_stop_iface(wiphy, wdev, GFP_KERNEL);
	unregister_netdevice(vif->ndev);
	vif->monitor_flag = 0;

	mutex_lock(&wl->vif_mutex);
	wilc_set_operation_mode(vif, 0, 0, 0);
	for (i = vif->idx; i < wl->vif_num; i++) {
		if ((i + 1) >= wl->vif_num) {
			wl->vif[i] = NULL;
		} else {
			vif = wl->vif[i + 1];
			vif->idx = i;
			wl->vif[i] = vif;
			wilc_set_operation_mode(vif, wilc_get_vif_idx(vif),
						vif->iftype, vif->idx);
		}
	}
	wl->vif_num--;
	mutex_unlock(&wl->vif_mutex);

	return 0;
}