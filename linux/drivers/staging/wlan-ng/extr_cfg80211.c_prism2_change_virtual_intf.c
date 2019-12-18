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
typedef  int u32 ;
struct wlandevice {int /*<<< orphan*/  macmode; } ;
struct wiphy {int dummy; } ;
struct vif_params {int dummy; } ;
struct net_device {TYPE_1__* ieee80211_ptr; struct wlandevice* ml_priv; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_2__ {int iftype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIDMIB_P2_STATIC_CNFPORTTYPE ; 
 int EFAULT ; 
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_ADHOC 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WLAN_MACMODE_ESS_STA ; 
 int /*<<< orphan*/  WLAN_MACMODE_IBSS_STA ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int prism2_domibset_uint32 (struct wlandevice*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prism2_change_virtual_intf(struct wiphy *wiphy,
				      struct net_device *dev,
				      enum nl80211_iftype type,
				      struct vif_params *params)
{
	struct wlandevice *wlandev = dev->ml_priv;
	u32 data;
	int result;
	int err = 0;

	switch (type) {
	case NL80211_IFTYPE_ADHOC:
		if (wlandev->macmode == WLAN_MACMODE_IBSS_STA)
			goto exit;
		wlandev->macmode = WLAN_MACMODE_IBSS_STA;
		data = 0;
		break;
	case NL80211_IFTYPE_STATION:
		if (wlandev->macmode == WLAN_MACMODE_ESS_STA)
			goto exit;
		wlandev->macmode = WLAN_MACMODE_ESS_STA;
		data = 1;
		break;
	default:
		netdev_warn(dev, "Operation mode: %d not support\n", type);
		return -EOPNOTSUPP;
	}

	/* Set Operation mode to the PORT TYPE RID */
	result = prism2_domibset_uint32(wlandev,
					DIDMIB_P2_STATIC_CNFPORTTYPE,
					data);

	if (result)
		err = -EFAULT;

	dev->ieee80211_ptr->iftype = type;

exit:
	return err;
}