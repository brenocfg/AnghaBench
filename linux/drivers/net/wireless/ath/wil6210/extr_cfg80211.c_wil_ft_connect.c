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
struct wmi_ft_auth_cmd {int /*<<< orphan*/  bssid; scalar_t__ channel; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {int /*<<< orphan*/  status; int /*<<< orphan*/  connect_timer; int /*<<< orphan*/  mid; int /*<<< orphan*/  privacy; } ;
struct wil6210_priv {int /*<<< orphan*/  fw_capabilities; } ;
struct net_device {int dummy; } ;
struct cfg80211_connect_params {int /*<<< orphan*/  bssid; TYPE_1__* channel; scalar_t__ pbss; int /*<<< orphan*/  privacy; int /*<<< orphan*/  prev_bssid; } ;
typedef  int /*<<< orphan*/  auth_cmd ;
struct TYPE_2__ {scalar_t__ hw_value; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WMI_FT_AUTH_CMDID ; 
 int /*<<< orphan*/  WMI_FW_CAPABILITY_FT_ROAMING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (struct wmi_ft_auth_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_vif_ft_roam ; 
 int /*<<< orphan*/  wil_vif_fwconnected ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_ft_auth_cmd*,int) ; 

__attribute__((used)) static int wil_ft_connect(struct wiphy *wiphy,
			  struct net_device *ndev,
			  struct cfg80211_connect_params *sme)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	struct wmi_ft_auth_cmd auth_cmd;
	int rc;

	if (!test_bit(WMI_FW_CAPABILITY_FT_ROAMING, wil->fw_capabilities)) {
		wil_err(wil, "FT: FW does not support FT roaming\n");
		return -EOPNOTSUPP;
	}

	if (!sme->prev_bssid) {
		wil_err(wil, "FT: prev_bssid was not set\n");
		return -EINVAL;
	}

	if (ether_addr_equal(sme->prev_bssid, sme->bssid)) {
		wil_err(wil, "FT: can not roam to same AP\n");
		return -EINVAL;
	}

	if (!test_bit(wil_vif_fwconnected, vif->status)) {
		wil_err(wil, "FT: roam while not connected\n");
		return -EINVAL;
	}

	if (vif->privacy != sme->privacy) {
		wil_err(wil, "FT: privacy mismatch, current (%d) roam (%d)\n",
			vif->privacy, sme->privacy);
		return -EINVAL;
	}

	if (sme->pbss) {
		wil_err(wil, "FT: roam is not valid for PBSS\n");
		return -EINVAL;
	}

	memset(&auth_cmd, 0, sizeof(auth_cmd));
	auth_cmd.channel = sme->channel->hw_value - 1;
	ether_addr_copy(auth_cmd.bssid, sme->bssid);

	wil_info(wil, "FT: roaming\n");

	set_bit(wil_vif_ft_roam, vif->status);
	rc = wmi_send(wil, WMI_FT_AUTH_CMDID, vif->mid,
		      &auth_cmd, sizeof(auth_cmd));
	if (rc == 0)
		mod_timer(&vif->connect_timer,
			  jiffies + msecs_to_jiffies(5000));
	else
		clear_bit(wil_vif_ft_roam, vif->status);

	return rc;
}