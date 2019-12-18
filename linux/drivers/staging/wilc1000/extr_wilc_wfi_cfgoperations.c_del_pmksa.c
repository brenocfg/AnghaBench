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
typedef  size_t u32 ;
struct wiphy {int dummy; } ;
struct TYPE_3__ {size_t numpmkid; TYPE_2__* pmkidlist; } ;
struct wilc_priv {TYPE_1__ pmkid_list; } ;
struct wilc_vif {struct wilc_priv priv; } ;
struct wilc_pmkid {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_pmksa {int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  pmkid; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WLAN_PMKID_LEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int del_pmksa(struct wiphy *wiphy, struct net_device *netdev,
		     struct cfg80211_pmksa *pmksa)
{
	u32 i;
	int ret = 0;
	struct wilc_vif *vif = netdev_priv(netdev);
	struct wilc_priv *priv = &vif->priv;

	for (i = 0; i < priv->pmkid_list.numpmkid; i++)	{
		if (!memcmp(pmksa->bssid, priv->pmkid_list.pmkidlist[i].bssid,
			    ETH_ALEN)) {
			memset(&priv->pmkid_list.pmkidlist[i], 0,
			       sizeof(struct wilc_pmkid));
			break;
		}
	}

	if (i < priv->pmkid_list.numpmkid && priv->pmkid_list.numpmkid > 0) {
		for (; i < (priv->pmkid_list.numpmkid - 1); i++) {
			memcpy(priv->pmkid_list.pmkidlist[i].bssid,
			       priv->pmkid_list.pmkidlist[i + 1].bssid,
			       ETH_ALEN);
			memcpy(priv->pmkid_list.pmkidlist[i].pmkid,
			       priv->pmkid_list.pmkidlist[i + 1].pmkid,
			       WLAN_PMKID_LEN);
		}
		priv->pmkid_list.numpmkid--;
	} else {
		ret = -EINVAL;
	}

	return ret;
}