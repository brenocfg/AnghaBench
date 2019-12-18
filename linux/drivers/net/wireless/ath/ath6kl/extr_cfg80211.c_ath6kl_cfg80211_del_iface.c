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
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  list; } ;
struct ath6kl {int /*<<< orphan*/  flag; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_READY ; 
 int /*<<< orphan*/  ath6kl_cfg80211_vif_cleanup (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_cfg80211_vif_stop (struct ath6kl_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct ath6kl_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ath6kl* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ath6kl_cfg80211_del_iface(struct wiphy *wiphy,
				     struct wireless_dev *wdev)
{
	struct ath6kl *ar = wiphy_priv(wiphy);
	struct ath6kl_vif *vif = netdev_priv(wdev->netdev);

	spin_lock_bh(&ar->list_lock);
	list_del(&vif->list);
	spin_unlock_bh(&ar->list_lock);

	ath6kl_cfg80211_vif_stop(vif, test_bit(WMI_READY, &ar->flag));

	rtnl_lock();
	ath6kl_cfg80211_vif_cleanup(vif);
	rtnl_unlock();

	return 0;
}