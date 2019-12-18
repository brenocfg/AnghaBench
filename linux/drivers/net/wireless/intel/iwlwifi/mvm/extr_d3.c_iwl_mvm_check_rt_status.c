#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct error_table_start   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iwl_mvm {TYPE_2__* trans; } ;
struct ieee80211_vif {int dummy; } ;
struct cfg80211_wowlan_wakeup {int rfkill_release; } ;
typedef  int /*<<< orphan*/  err_info ;
struct error_table_start {scalar_t__ valid; scalar_t__ error_id; } ;
struct TYPE_4__ {scalar_t__* lmac_error_event_table; } ;
struct TYPE_5__ {TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RF_KILL_INDICATOR_FOR_WOWLAN ; 
 int /*<<< orphan*/  ieee80211_report_wowlan_wakeup (struct ieee80211_vif*,struct cfg80211_wowlan_wakeup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_read_mem_bytes (TYPE_2__*,scalar_t__,TYPE_3__*,int) ; 

__attribute__((used)) static int iwl_mvm_check_rt_status(struct iwl_mvm *mvm,
				   struct ieee80211_vif *vif)
{
	u32 base = mvm->trans->dbg.lmac_error_event_table[0];
	struct error_table_start {
		/* cf. struct iwl_error_event_table */
		u32 valid;
		u32 error_id;
	} err_info;

	iwl_trans_read_mem_bytes(mvm->trans, base,
				 &err_info, sizeof(err_info));

	if (err_info.valid &&
	    err_info.error_id == RF_KILL_INDICATOR_FOR_WOWLAN) {
		struct cfg80211_wowlan_wakeup wakeup = {
			.rfkill_release = true,
		};
		ieee80211_report_wowlan_wakeup(vif, &wakeup, GFP_KERNEL);
	}
	return err_info.valid;
}