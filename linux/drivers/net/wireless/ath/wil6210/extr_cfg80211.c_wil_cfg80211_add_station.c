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
struct wiphy {int dummy; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;
struct station_parameters {int /*<<< orphan*/  aid; int /*<<< orphan*/  sta_flags_set; int /*<<< orphan*/  sta_flags_mask; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WIL_MAX_DMG_AID ; 
 int /*<<< orphan*/  disable_ap_sme ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_new_sta (struct wil6210_vif*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wil_cfg80211_add_station(struct wiphy *wiphy,
				    struct net_device *dev,
				    const u8 *mac,
				    struct station_parameters *params)
{
	struct wil6210_vif *vif = ndev_to_vif(dev);
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil_dbg_misc(wil, "add station %pM aid %d mid %d mask 0x%x set 0x%x\n",
		     mac, params->aid, vif->mid,
		     params->sta_flags_mask, params->sta_flags_set);

	if (!disable_ap_sme) {
		wil_err(wil, "not supported with AP SME enabled\n");
		return -EOPNOTSUPP;
	}

	if (params->aid > WIL_MAX_DMG_AID) {
		wil_err(wil, "invalid aid\n");
		return -EINVAL;
	}

	return wmi_new_sta(vif, mac, params->aid);
}