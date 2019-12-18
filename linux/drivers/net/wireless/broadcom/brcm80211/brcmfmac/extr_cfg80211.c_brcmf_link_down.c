#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct brcmf_pub {TYPE_1__* bus_if; } ;
struct TYPE_6__ {scalar_t__ use_fwsup; } ;
struct TYPE_5__ {scalar_t__ iftype; int /*<<< orphan*/  netdev; int /*<<< orphan*/  wiphy; } ;
struct brcmf_cfg80211_vif {TYPE_3__ profile; int /*<<< orphan*/  ifp; int /*<<< orphan*/  sme_state; TYPE_2__ wdev; } ;
struct brcmf_cfg80211_info {int /*<<< orphan*/  scan_status; struct brcmf_pub* pub; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_BTCOEX_ENABLED ; 
 scalar_t__ BRCMF_BUS_UP ; 
 int /*<<< orphan*/  BRCMF_C_DISASSOC ; 
 scalar_t__ BRCMF_PROFILE_FWSUP_NONE ; 
 int /*<<< orphan*/  BRCMF_SCAN_STATUS_SUPPRESS ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_btcoex_set_mode (struct brcmf_cfg80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ brcmf_fil_cmd_data_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_set_pmk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_link_down(struct brcmf_cfg80211_vif *vif, u16 reason)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(vif->wdev.wiphy);
	struct brcmf_pub *drvr = cfg->pub;
	bool bus_up = drvr->bus_if->state == BRCMF_BUS_UP;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");

	if (test_and_clear_bit(BRCMF_VIF_STATUS_CONNECTED, &vif->sme_state)) {
		if (bus_up) {
			brcmf_dbg(INFO, "Call WLC_DISASSOC to stop excess roaming\n");
			err = brcmf_fil_cmd_data_set(vif->ifp,
						     BRCMF_C_DISASSOC, NULL, 0);
			if (err)
				bphy_err(drvr, "WLC_DISASSOC failed (%d)\n",
					 err);
		}

		if ((vif->wdev.iftype == NL80211_IFTYPE_STATION) ||
		    (vif->wdev.iftype == NL80211_IFTYPE_P2P_CLIENT))
			cfg80211_disconnected(vif->wdev.netdev, reason, NULL, 0,
					      true, GFP_KERNEL);
	}
	clear_bit(BRCMF_VIF_STATUS_CONNECTING, &vif->sme_state);
	clear_bit(BRCMF_SCAN_STATUS_SUPPRESS, &cfg->scan_status);
	brcmf_btcoex_set_mode(vif, BRCMF_BTCOEX_ENABLED, 0);
	if (vif->profile.use_fwsup != BRCMF_PROFILE_FWSUP_NONE) {
		if (bus_up)
			brcmf_set_pmk(vif->ifp, NULL, 0);
		vif->profile.use_fwsup = BRCMF_PROFILE_FWSUP_NONE;
	}
	brcmf_dbg(TRACE, "Exit\n");
}