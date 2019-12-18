#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dbg_fixed_rate; int /*<<< orphan*/  last_rssi; int /*<<< orphan*/  chain_signal; scalar_t__ chains; int /*<<< orphan*/  sta_id; struct iwl_mvm* drv; } ;
struct iwl_lq_sta_rs_fw {TYPE_1__ pers; scalar_t__ last_rate_n_flags; } ;
struct TYPE_4__ {struct iwl_lq_sta_rs_fw rs_fw; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  sta_id; TYPE_2__ lq_sta; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  S8_MIN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void iwl_mvm_rs_add_sta(struct iwl_mvm *mvm, struct iwl_mvm_sta *mvmsta)
{
	struct iwl_lq_sta_rs_fw *lq_sta = &mvmsta->lq_sta.rs_fw;

	IWL_DEBUG_RATE(mvm, "create station rate scale window\n");

	lq_sta->pers.drv = mvm;
	lq_sta->pers.sta_id = mvmsta->sta_id;
	lq_sta->pers.chains = 0;
	memset(lq_sta->pers.chain_signal, 0, sizeof(lq_sta->pers.chain_signal));
	lq_sta->pers.last_rssi = S8_MIN;
	lq_sta->last_rate_n_flags = 0;

#ifdef CONFIG_MAC80211_DEBUGFS
	lq_sta->pers.dbg_fixed_rate = 0;
#endif
}