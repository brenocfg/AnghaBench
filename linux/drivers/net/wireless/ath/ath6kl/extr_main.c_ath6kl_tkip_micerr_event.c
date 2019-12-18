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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tsc ;
struct ath6kl_vif {scalar_t__ nw_type; int /*<<< orphan*/  ndev; struct ath6kl* ar; } ;
struct ath6kl_sta {int /*<<< orphan*/  mac; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 scalar_t__ AP_NETWORK ; 
 int /*<<< orphan*/  ATH6KL_DBG_TRC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_KEYTYPE_PAIRWISE ; 
 int /*<<< orphan*/  ath6kl_cfg80211_tkip_micerr_event (struct ath6kl_vif*,int,int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct ath6kl_sta* ath6kl_find_sta_by_aid (struct ath6kl*,int) ; 
 int /*<<< orphan*/  cfg80211_michael_mic_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void ath6kl_tkip_micerr_event(struct ath6kl_vif *vif, u8 keyid, bool ismcast)
{
	struct ath6kl_sta *sta;
	struct ath6kl *ar = vif->ar;
	u8 tsc[6];

	/*
	 * For AP case, keyid will have aid of STA which sent pkt with
	 * MIC error. Use this aid to get MAC & send it to hostapd.
	 */
	if (vif->nw_type == AP_NETWORK) {
		sta = ath6kl_find_sta_by_aid(ar, (keyid >> 2));
		if (!sta)
			return;

		ath6kl_dbg(ATH6KL_DBG_TRC,
			   "ap tkip mic error received from aid=%d\n", keyid);

		memset(tsc, 0, sizeof(tsc)); /* FIX: get correct TSC */
		cfg80211_michael_mic_failure(vif->ndev, sta->mac,
					     NL80211_KEYTYPE_PAIRWISE, keyid,
					     tsc, GFP_KERNEL);
	} else {
		ath6kl_cfg80211_tkip_micerr_event(vif, keyid, ismcast);
	}
}