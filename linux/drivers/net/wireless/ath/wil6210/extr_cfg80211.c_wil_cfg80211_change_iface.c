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
struct wireless_dev {int iftype; } ;
struct wiphy {scalar_t__ n_iface_combinations; } ;
struct wil6210_vif {scalar_t__ mid; } ;
struct wil6210_priv {int /*<<< orphan*/  monitor_flags; int /*<<< orphan*/  mutex; } ;
struct vif_params {int /*<<< orphan*/  flags; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_MONITOR 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  __wil_down (struct wil6210_priv*) ; 
 int __wil_up (struct wil6210_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct wireless_dev* vif_to_wdev (struct wil6210_vif*) ; 
 int wil_cfg80211_validate_change_iface (struct wil6210_priv*,struct wil6210_vif*,int) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int) ; 
 scalar_t__ wil_has_active_ifaces (struct wil6210_priv*,int,int) ; 
 int /*<<< orphan*/  wil_has_other_active_ifaces (struct wil6210_priv*,struct net_device*,int,int) ; 
 int /*<<< orphan*/  wil_is_recovery_blocked (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_is_safe_switch (int,int) ; 
 int /*<<< orphan*/  wil_vif_prepare_stop (struct wil6210_vif*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_port_allocate (struct wil6210_priv*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int wmi_port_delete (struct wil6210_priv*,scalar_t__) ; 

__attribute__((used)) static int wil_cfg80211_change_iface(struct wiphy *wiphy,
				     struct net_device *ndev,
				     enum nl80211_iftype type,
				     struct vif_params *params)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	struct wireless_dev *wdev = vif_to_wdev(vif);
	int rc;
	bool fw_reset = false;

	wil_dbg_misc(wil, "change_iface: type=%d\n", type);

	if (wiphy->n_iface_combinations) {
		rc = wil_cfg80211_validate_change_iface(wil, vif, type);
		if (rc) {
			wil_err(wil, "iface validation failed, err=%d\n", rc);
			return rc;
		}
	}

	/* do not reset FW when there are active VIFs,
	 * because it can cause significant disruption
	 */
	if (!wil_has_other_active_ifaces(wil, ndev, true, false) &&
	    netif_running(ndev) && !wil_is_recovery_blocked(wil) &&
	    !wil_is_safe_switch(wdev->iftype, type)) {
		wil_dbg_misc(wil, "interface is up. resetting...\n");
		mutex_lock(&wil->mutex);
		__wil_down(wil);
		rc = __wil_up(wil);
		mutex_unlock(&wil->mutex);

		if (rc)
			return rc;
		fw_reset = true;
	}

	switch (type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_P2P_GO:
		break;
	case NL80211_IFTYPE_MONITOR:
		if (params->flags)
			wil->monitor_flags = params->flags;
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (vif->mid != 0 && wil_has_active_ifaces(wil, true, false)) {
		if (!fw_reset)
			wil_vif_prepare_stop(vif);
		rc = wmi_port_delete(wil, vif->mid);
		if (rc)
			return rc;
		rc = wmi_port_allocate(wil, vif->mid, ndev->dev_addr, type);
		if (rc)
			return rc;
	}

	wdev->iftype = type;
	return 0;
}