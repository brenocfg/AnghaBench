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
typedef  int u32 ;
struct rs_bfer_active_iter_data {struct iwl_mvm_sta* bfer_mvmsta; struct ieee80211_sta* exclude_sta; } ;
struct iwl_lq_cmd {int /*<<< orphan*/  ss_params; } ;
struct TYPE_3__ {struct iwl_lq_cmd lq; } ;
struct TYPE_4__ {TYPE_1__ rs_drv; } ;
struct iwl_mvm_sta {TYPE_2__ lq_sta; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int LQ_SS_BFER_ALLOWED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_bfer_active_iter(void *_data,
				struct ieee80211_sta *sta)
{
	struct rs_bfer_active_iter_data *data = _data;
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct iwl_lq_cmd *lq_cmd = &mvmsta->lq_sta.rs_drv.lq;
	u32 ss_params = le32_to_cpu(lq_cmd->ss_params);

	if (sta == data->exclude_sta)
		return;

	/* The current sta has BFER allowed */
	if (ss_params & LQ_SS_BFER_ALLOWED) {
		WARN_ON_ONCE(data->bfer_mvmsta != NULL);

		data->bfer_mvmsta = mvmsta;
	}
}