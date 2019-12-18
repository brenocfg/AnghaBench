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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int iftype; int /*<<< orphan*/ * netdev; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct vif_params {int use_4addr; int /*<<< orphan*/ * macaddr; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; } ;
struct qtnf_vif {int vifid; struct wireless_dev wdev; int /*<<< orphan*/ * netdev; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  bss_priority; int /*<<< orphan*/  bssid; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 struct wireless_dev* ERR_PTR (int) ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  QTNF_DEF_BSS_PRIORITY ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wireless_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int qtnf_cmd_send_add_intf (struct qtnf_vif*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_cmd_send_del_intf (struct qtnf_vif*) ; 
 int qtnf_core_net_attach (struct qtnf_wmac*,struct qtnf_vif*,char const*,unsigned char) ; 
 struct qtnf_vif* qtnf_mac_get_free_vif (struct qtnf_wmac*) ; 
 int qtnf_validate_iface_combinations (struct wiphy*,int /*<<< orphan*/ *,int) ; 
 struct qtnf_wmac* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static struct wireless_dev *qtnf_add_virtual_intf(struct wiphy *wiphy,
						  const char *name,
						  unsigned char name_assign_t,
						  enum nl80211_iftype type,
						  struct vif_params *params)
{
	struct qtnf_wmac *mac;
	struct qtnf_vif *vif;
	u8 *mac_addr = NULL;
	int use4addr = 0;
	int ret;

	mac = wiphy_priv(wiphy);

	if (!mac)
		return ERR_PTR(-EFAULT);

	ret = qtnf_validate_iface_combinations(wiphy, NULL, type);
	if (ret) {
		pr_err("MAC%u invalid combination: failed to add type %d\n",
		       mac->macid, type);
		return ERR_PTR(ret);
	}

	switch (type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_AP:
		vif = qtnf_mac_get_free_vif(mac);
		if (!vif) {
			pr_err("MAC%u: no free VIF available\n", mac->macid);
			return ERR_PTR(-EFAULT);
		}

		eth_zero_addr(vif->mac_addr);
		eth_zero_addr(vif->bssid);
		vif->bss_priority = QTNF_DEF_BSS_PRIORITY;
		memset(&vif->wdev, 0, sizeof(vif->wdev));
		vif->wdev.wiphy = wiphy;
		vif->wdev.iftype = type;
		break;
	default:
		pr_err("MAC%u: unsupported IF type %d\n", mac->macid, type);
		return ERR_PTR(-ENOTSUPP);
	}

	if (params) {
		mac_addr = params->macaddr;
		use4addr = params->use_4addr;
	}

	ret = qtnf_cmd_send_add_intf(vif, type, use4addr, mac_addr);
	if (ret) {
		pr_err("VIF%u.%u: failed to add VIF %pM\n",
		       mac->macid, vif->vifid, mac_addr);
		goto err_cmd;
	}

	if (!is_valid_ether_addr(vif->mac_addr)) {
		pr_err("VIF%u.%u: FW reported bad MAC: %pM\n",
		       mac->macid, vif->vifid, vif->mac_addr);
		ret = -EINVAL;
		goto err_mac;
	}

	ret = qtnf_core_net_attach(mac, vif, name, name_assign_t);
	if (ret) {
		pr_err("VIF%u.%u: failed to attach netdev\n", mac->macid,
		       vif->vifid);
		goto err_net;
	}

	vif->wdev.netdev = vif->netdev;
	return &vif->wdev;

err_net:
	vif->netdev = NULL;
err_mac:
	qtnf_cmd_send_del_intf(vif);
err_cmd:
	vif->wdev.iftype = NL80211_IFTYPE_UNSPECIFIED;

	return ERR_PTR(ret);
}