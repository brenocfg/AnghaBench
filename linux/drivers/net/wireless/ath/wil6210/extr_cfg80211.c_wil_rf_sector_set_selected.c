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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {scalar_t__ mid; int /*<<< orphan*/  status; } ;
struct wil6210_priv {scalar_t__ max_assoc_sta; TYPE_1__* sta; int /*<<< orphan*/  fw_capabilities; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {scalar_t__ mid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 size_t QCA_ATTR_DMG_RF_SECTOR_INDEX ; 
 int /*<<< orphan*/  QCA_ATTR_DMG_RF_SECTOR_MAX ; 
 size_t QCA_ATTR_DMG_RF_SECTOR_TYPE ; 
 scalar_t__ QCA_ATTR_DMG_RF_SECTOR_TYPE_MAX ; 
 size_t QCA_ATTR_MAC_ADDR ; 
 scalar_t__ WIL_CID_ALL ; 
 scalar_t__ WIL_MAX_RF_SECTORS ; 
 int /*<<< orphan*/  WMI_FW_CAPABILITY_RF_SECTORS ; 
 scalar_t__ WMI_INVALID_RF_SECTOR_INDEX ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (scalar_t__*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_get_u16 (struct nlattr*) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 
 int nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wil6210_vif* wdev_to_vif (struct wil6210_priv*,struct wireless_dev*) ; 
 struct wil6210_priv* wdev_to_wil (struct wireless_dev*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int wil_find_cid (struct wil6210_priv*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  wil_rf_sector_policy ; 
 int wil_rf_sector_wmi_set_selected (struct wil6210_priv*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wil_vif_fwconnected ; 

__attribute__((used)) static int wil_rf_sector_set_selected(struct wiphy *wiphy,
				      struct wireless_dev *wdev,
				      const void *data, int data_len)
{
	struct wil6210_priv *wil = wdev_to_wil(wdev);
	struct wil6210_vif *vif = wdev_to_vif(wil, wdev);
	int rc;
	struct nlattr *tb[QCA_ATTR_DMG_RF_SECTOR_MAX + 1];
	u16 sector_index;
	u8 sector_type, mac_addr[ETH_ALEN], i;
	int cid = 0;

	if (!test_bit(WMI_FW_CAPABILITY_RF_SECTORS, wil->fw_capabilities))
		return -EOPNOTSUPP;

	rc = nla_parse_deprecated(tb, QCA_ATTR_DMG_RF_SECTOR_MAX, data,
				  data_len, wil_rf_sector_policy, NULL);
	if (rc) {
		wil_err(wil, "Invalid rf sector ATTR\n");
		return rc;
	}

	if (!tb[QCA_ATTR_DMG_RF_SECTOR_INDEX] ||
	    !tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]) {
		wil_err(wil, "Invalid rf sector spec\n");
		return -EINVAL;
	}

	sector_index = nla_get_u16(
		tb[QCA_ATTR_DMG_RF_SECTOR_INDEX]);
	if (sector_index >= WIL_MAX_RF_SECTORS &&
	    sector_index != WMI_INVALID_RF_SECTOR_INDEX) {
		wil_err(wil, "Invalid sector index %d\n", sector_index);
		return -EINVAL;
	}

	sector_type = nla_get_u8(tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]);
	if (sector_type >= QCA_ATTR_DMG_RF_SECTOR_TYPE_MAX) {
		wil_err(wil, "Invalid sector type %d\n", sector_type);
		return -EINVAL;
	}

	if (tb[QCA_ATTR_MAC_ADDR]) {
		ether_addr_copy(mac_addr, nla_data(tb[QCA_ATTR_MAC_ADDR]));
		if (!is_broadcast_ether_addr(mac_addr)) {
			cid = wil_find_cid(wil, vif->mid, mac_addr);
			if (cid < 0) {
				wil_err(wil, "invalid MAC address %pM\n",
					mac_addr);
				return -ENOENT;
			}
		} else {
			if (sector_index != WMI_INVALID_RF_SECTOR_INDEX) {
				wil_err(wil, "broadcast MAC valid only with unlocking\n");
				return -EINVAL;
			}
			cid = -1;
		}
	} else {
		if (test_bit(wil_vif_fwconnected, vif->status)) {
			wil_err(wil, "must specify MAC address when connected\n");
			return -EINVAL;
		}
		/* otherwise, using cid=0 for unassociated station */
	}

	if (cid >= 0) {
		rc = wil_rf_sector_wmi_set_selected(wil, vif->mid, sector_index,
						    sector_type, cid);
	} else {
		/* unlock all cids */
		rc = wil_rf_sector_wmi_set_selected(
			wil, vif->mid, WMI_INVALID_RF_SECTOR_INDEX,
			sector_type, WIL_CID_ALL);
		if (rc == -EINVAL) {
			for (i = 0; i < wil->max_assoc_sta; i++) {
				if (wil->sta[i].mid != vif->mid)
					continue;
				rc = wil_rf_sector_wmi_set_selected(
					wil, vif->mid,
					WMI_INVALID_RF_SECTOR_INDEX,
					sector_type, i);
				/* the FW will silently ignore and return
				 * success for unused cid, so abort the loop
				 * on any other error
				 */
				if (rc) {
					wil_err(wil, "unlock cid %d failed with status %d\n",
						i, rc);
					break;
				}
			}
		}
	}

	return rc;
}