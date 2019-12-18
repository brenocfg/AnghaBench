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
struct wil6210_vif {scalar_t__ gtk_len; int /*<<< orphan*/  gtk; int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/  assocresp_ies; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/  proberesp_ies; int /*<<< orphan*/  proberesp_len; int /*<<< orphan*/  proberesp; scalar_t__ ssid_len; int /*<<< orphan*/  status; int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIL_DEFAULT_BUS_REQUEST_KBPS ; 
 int /*<<< orphan*/  WMI_MAX_KEY_LEN ; 
 int /*<<< orphan*/  __wil_down (struct wil6210_priv*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_recovery_idle ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil6210_bus_request (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_bcast_fini (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_has_other_active_ifaces (struct wil6210_priv*,struct net_device*,int,int) ; 
 int /*<<< orphan*/  wil_memdup_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_set_recovery_state (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_status_resetting ; 
 int /*<<< orphan*/  wil_vif_ft_roam ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int /*<<< orphan*/  wmi_pcp_stop (struct wil6210_vif*) ; 

__attribute__((used)) static int wil_cfg80211_stop_ap(struct wiphy *wiphy,
				struct net_device *ndev)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	bool last;

	wil_dbg_misc(wil, "stop_ap, mid=%d\n", vif->mid);

	netif_carrier_off(ndev);
	last = !wil_has_other_active_ifaces(wil, ndev, false, true);
	if (last) {
		wil6210_bus_request(wil, WIL_DEFAULT_BUS_REQUEST_KBPS);
		wil_set_recovery_state(wil, fw_recovery_idle);
		set_bit(wil_status_resetting, wil->status);
	}

	mutex_lock(&wil->mutex);

	wmi_pcp_stop(vif);
	clear_bit(wil_vif_ft_roam, vif->status);
	vif->ssid_len = 0;
	wil_memdup_ie(&vif->proberesp, &vif->proberesp_len, NULL, 0);
	wil_memdup_ie(&vif->proberesp_ies, &vif->proberesp_ies_len, NULL, 0);
	wil_memdup_ie(&vif->assocresp_ies, &vif->assocresp_ies_len, NULL, 0);
	memset(vif->gtk, 0, WMI_MAX_KEY_LEN);
	vif->gtk_len = 0;

	if (last)
		__wil_down(wil);
	else
		wil_bcast_fini(vif);

	mutex_unlock(&wil->mutex);

	return 0;
}