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
struct wiphy {int dummy; } ;
struct vif_params {int dummy; } ;
struct net_device {int dummy; } ;
struct lbs_private {TYPE_1__* wdev; scalar_t__ iface_running; struct net_device* mesh_dev; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_2__ {int iftype; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 
 int lbs_set_iface_type (struct lbs_private*,int) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_change_intf(struct wiphy *wiphy, struct net_device *dev,
	enum nl80211_iftype type,
	       struct vif_params *params)
{
	struct lbs_private *priv = wiphy_priv(wiphy);
	int ret = 0;

	if (dev == priv->mesh_dev)
		return -EOPNOTSUPP;

	switch (type) {
	case NL80211_IFTYPE_MONITOR:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (priv->iface_running)
		ret = lbs_set_iface_type(priv, type);

	if (!ret)
		priv->wdev->iftype = type;

	return ret;
}