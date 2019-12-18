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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct vif_params {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct wireless_dev* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct wireless_dev*) ; 
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
 scalar_t__ PTR_ERR (struct wireless_dev*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 struct wireless_dev* brcmf_ap_add_vif (struct wiphy*,char const*,struct vif_params*) ; 
 int /*<<< orphan*/  brcmf_cfg80211_update_proto_addr_mode (struct wireless_dev*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,char const*,int) ; 
 struct wireless_dev* brcmf_p2p_add_vif (struct wiphy*,char const*,unsigned char,int,struct vif_params*) ; 
 int brcmf_vif_add_validate (struct brcmf_cfg80211_info*,int) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static struct wireless_dev *brcmf_cfg80211_add_iface(struct wiphy *wiphy,
						     const char *name,
						     unsigned char name_assign_type,
						     enum nl80211_iftype type,
						     struct vif_params *params)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct brcmf_pub *drvr = cfg->pub;
	struct wireless_dev *wdev;
	int err;

	brcmf_dbg(TRACE, "enter: %s type %d\n", name, type);
	err = brcmf_vif_add_validate(wiphy_to_cfg(wiphy), type);
	if (err) {
		bphy_err(drvr, "iface validation failed: err=%d\n", err);
		return ERR_PTR(err);
	}
	switch (type) {
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_WDS:
	case NL80211_IFTYPE_MONITOR:
	case NL80211_IFTYPE_MESH_POINT:
		return ERR_PTR(-EOPNOTSUPP);
	case NL80211_IFTYPE_AP:
		wdev = brcmf_ap_add_vif(wiphy, name, params);
		break;
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_P2P_DEVICE:
		wdev = brcmf_p2p_add_vif(wiphy, name, name_assign_type, type, params);
		break;
	case NL80211_IFTYPE_UNSPECIFIED:
	default:
		return ERR_PTR(-EINVAL);
	}

	if (IS_ERR(wdev))
		bphy_err(drvr, "add iface %s type %d failed: err=%d\n", name,
			 type, (int)PTR_ERR(wdev));
	else
		brcmf_cfg80211_update_proto_addr_mode(wdev);

	return wdev;
}