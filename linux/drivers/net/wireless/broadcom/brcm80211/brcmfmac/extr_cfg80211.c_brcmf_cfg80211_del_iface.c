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
struct wireless_dev {int iftype; struct net_device* netdev; } ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ ifp; } ;
struct brcmf_cfg80211_info {TYPE_1__ escan_info; int /*<<< orphan*/  scan_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_SCAN_STATUS_BUSY ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_ADHOC 138 
#define  NL80211_IFTYPE_AP 137 
#define  NL80211_IFTYPE_AP_VLAN 136 
#define  NL80211_IFTYPE_MESH_POINT 135 
#define  NL80211_IFTYPE_MONITOR 134 
#define  NL80211_IFTYPE_P2P_CLIENT 133 
#define  NL80211_IFTYPE_P2P_DEVICE 132 
#define  NL80211_IFTYPE_P2P_GO 131 
#define  NL80211_IFTYPE_STATION 130 
#define  NL80211_IFTYPE_UNSPECIFIED 129 
#define  NL80211_IFTYPE_WDS 128 
 int brcmf_cfg80211_del_ap_iface (struct wiphy*,struct wireless_dev*) ; 
 scalar_t__ brcmf_cfg80211_vif_event_armed (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_fil_iovar_int_set (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  brcmf_notify_escan_complete (struct brcmf_cfg80211_info*,scalar_t__,int,int) ; 
 int brcmf_p2p_del_vif (struct wiphy*,struct wireless_dev*) ; 
 struct net_device* cfg_to_ndev (struct brcmf_cfg80211_info*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static
int brcmf_cfg80211_del_iface(struct wiphy *wiphy, struct wireless_dev *wdev)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct net_device *ndev = wdev->netdev;

	if (ndev && ndev == cfg_to_ndev(cfg))
		return -ENOTSUPP;

	/* vif event pending in firmware */
	if (brcmf_cfg80211_vif_event_armed(cfg))
		return -EBUSY;

	if (ndev) {
		if (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status) &&
		    cfg->escan_info.ifp == netdev_priv(ndev))
			brcmf_notify_escan_complete(cfg, netdev_priv(ndev),
						    true, true);

		brcmf_fil_iovar_int_set(netdev_priv(ndev), "mpc", 1);
	}

	switch (wdev->iftype) {
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_WDS:
	case NL80211_IFTYPE_MONITOR:
	case NL80211_IFTYPE_MESH_POINT:
		return -EOPNOTSUPP;
	case NL80211_IFTYPE_AP:
		return brcmf_cfg80211_del_ap_iface(wiphy, wdev);
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_P2P_DEVICE:
		return brcmf_p2p_del_vif(wiphy, wdev);
	case NL80211_IFTYPE_UNSPECIFIED:
	default:
		return -EINVAL;
	}
	return -EOPNOTSUPP;
}