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
struct net_device {int dummy; } ;
struct cfg80211_pmksa {int /*<<< orphan*/  pmkid; int /*<<< orphan*/  bssid; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 int ath6kl_wmi_setpmkid_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ath6kl_del_pmksa(struct wiphy *wiphy, struct net_device *netdev,
			    struct cfg80211_pmksa *pmksa)
{
	struct ath6kl *ar = ath6kl_priv(netdev);
	struct ath6kl_vif *vif = netdev_priv(netdev);

	return ath6kl_wmi_setpmkid_cmd(ar->wmi, vif->fw_vif_idx, pmksa->bssid,
				       pmksa->pmkid, false);
}