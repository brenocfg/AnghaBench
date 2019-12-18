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
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct wil6210_vif {int locally_generated_disc; int /*<<< orphan*/  mid; int /*<<< orphan*/  status; } ;
struct wil6210_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIL6210_DISCONNECT_TO_MS ; 
 int /*<<< orphan*/  WMI_DISCONNECT_CMDID ; 
 int /*<<< orphan*/  WMI_DISCONNECT_EVENTID ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_vif_fwconnected ; 
 int /*<<< orphan*/  wil_vif_fwconnecting ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_call (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wil_cfg80211_disconnect(struct wiphy *wiphy,
				   struct net_device *ndev,
				   u16 reason_code)
{
	int rc;
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(ndev);

	wil_dbg_misc(wil, "disconnect: reason=%d, mid=%d\n",
		     reason_code, vif->mid);

	if (!(test_bit(wil_vif_fwconnecting, vif->status) ||
	      test_bit(wil_vif_fwconnected, vif->status))) {
		wil_err(wil, "Disconnect was called while disconnected\n");
		return 0;
	}

	vif->locally_generated_disc = true;
	rc = wmi_call(wil, WMI_DISCONNECT_CMDID, vif->mid, NULL, 0,
		      WMI_DISCONNECT_EVENTID, NULL, 0,
		      WIL6210_DISCONNECT_TO_MS);
	if (rc)
		wil_err(wil, "disconnect error %d\n", rc);

	return rc;
}