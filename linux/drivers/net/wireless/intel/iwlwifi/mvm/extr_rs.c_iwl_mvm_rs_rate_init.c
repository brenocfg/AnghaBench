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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {TYPE_1__ pers; } ;
struct TYPE_6__ {TYPE_2__ rs_drv; } ;
struct iwl_mvm_sta {TYPE_3__ lq_sta; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 scalar_t__ iwl_mvm_has_tlc_offload (struct iwl_mvm*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  rs_drv_rate_init (struct iwl_mvm*,struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  rs_fw_rate_init (struct iwl_mvm*,struct ieee80211_sta*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iwl_mvm_rs_rate_init(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			  enum nl80211_band band, bool update)
{
	if (iwl_mvm_has_tlc_offload(mvm)) {
		rs_fw_rate_init(mvm, sta, band, update);
	} else {
		struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

		spin_lock(&mvmsta->lq_sta.rs_drv.pers.lock);
		rs_drv_rate_init(mvm, sta, band);
		spin_unlock(&mvmsta->lq_sta.rs_drv.pers.lock);
	}
}