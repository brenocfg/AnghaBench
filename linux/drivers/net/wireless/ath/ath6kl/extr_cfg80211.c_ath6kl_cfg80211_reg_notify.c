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
typedef  int u32 ;
struct wiphy {TYPE_1__** bands; } ;
struct regulatory_request {scalar_t__ user_reg_hint_type; int /*<<< orphan*/ * alpha2; int /*<<< orphan*/  initiator; scalar_t__ processed; scalar_t__ intersect; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;
struct TYPE_2__ {int n_bitrates; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WLAN_CFG ; 
 int /*<<< orphan*/  ATH6KL_FG_SCAN_INTERVAL ; 
 scalar_t__ NL80211_USER_REG_HINT_CELL_BASE ; 
 int NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  WMI_LONG_SCAN ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_wmi_beginscan_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int ath6kl_wmi_set_regdomain_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ath6kl* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static void ath6kl_cfg80211_reg_notify(struct wiphy *wiphy,
				       struct regulatory_request *request)
{
	struct ath6kl *ar = wiphy_priv(wiphy);
	u32 rates[NUM_NL80211_BANDS];
	int ret, i;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
		   "cfg reg_notify %c%c%s%s initiator %d hint_type %d\n",
		   request->alpha2[0], request->alpha2[1],
		   request->intersect ? " intersect" : "",
		   request->processed ? " processed" : "",
		   request->initiator, request->user_reg_hint_type);

	if (request->user_reg_hint_type != NL80211_USER_REG_HINT_CELL_BASE)
		return;

	ret = ath6kl_wmi_set_regdomain_cmd(ar->wmi, request->alpha2);
	if (ret) {
		ath6kl_err("failed to set regdomain: %d\n", ret);
		return;
	}

	/*
	 * Firmware will apply the regdomain change only after a scan is
	 * issued and it will send a WMI_REGDOMAIN_EVENTID when it has been
	 * changed.
	 */

	for (i = 0; i < NUM_NL80211_BANDS; i++)
		if (wiphy->bands[i])
			rates[i] = (1 << wiphy->bands[i]->n_bitrates) - 1;


	ret = ath6kl_wmi_beginscan_cmd(ar->wmi, 0, WMI_LONG_SCAN, false,
				       false, 0, ATH6KL_FG_SCAN_INTERVAL,
				       0, NULL, false, rates);
	if (ret) {
		ath6kl_err("failed to start scan for a regdomain change: %d\n",
			   ret);
		return;
	}
}