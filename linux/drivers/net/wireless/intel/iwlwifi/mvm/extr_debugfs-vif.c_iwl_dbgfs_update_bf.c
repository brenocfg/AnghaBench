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
struct iwl_dbgfs_bf {int mask; int bf_energy_delta; int bf_roaming_energy_delta; int bf_roaming_state; int bf_temp_threshold; int bf_temp_fast_filter; int bf_temp_slow_filter; int bf_enable_beacon_filter; int bf_debug_flag; int bf_escape_timer; int ba_enable_beacon_abort; int ba_escape_timer; } ;
struct iwl_mvm_vif {struct iwl_dbgfs_bf dbgfs_bf; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum iwl_dbgfs_bf_mask { ____Placeholder_iwl_dbgfs_bf_mask } iwl_dbgfs_bf_mask ;

/* Variables and functions */
#define  MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT 138 
#define  MVM_DEBUGFS_BA_ESCAPE_TIMER 137 
#define  MVM_DEBUGFS_BF_DEBUG_FLAG 136 
#define  MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER 135 
#define  MVM_DEBUGFS_BF_ENERGY_DELTA 134 
#define  MVM_DEBUGFS_BF_ESCAPE_TIMER 133 
#define  MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA 132 
#define  MVM_DEBUGFS_BF_ROAMING_STATE 131 
#define  MVM_DEBUGFS_BF_TEMP_FAST_FILTER 130 
#define  MVM_DEBUGFS_BF_TEMP_SLOW_FILTER 129 
#define  MVM_DEBUGFS_BF_TEMP_THRESHOLD 128 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_dbgfs_update_bf(struct ieee80211_vif *vif,
				enum iwl_dbgfs_bf_mask param, int value)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_dbgfs_bf *dbgfs_bf = &mvmvif->dbgfs_bf;

	dbgfs_bf->mask |= param;

	switch (param) {
	case MVM_DEBUGFS_BF_ENERGY_DELTA:
		dbgfs_bf->bf_energy_delta = value;
		break;
	case MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA:
		dbgfs_bf->bf_roaming_energy_delta = value;
		break;
	case MVM_DEBUGFS_BF_ROAMING_STATE:
		dbgfs_bf->bf_roaming_state = value;
		break;
	case MVM_DEBUGFS_BF_TEMP_THRESHOLD:
		dbgfs_bf->bf_temp_threshold = value;
		break;
	case MVM_DEBUGFS_BF_TEMP_FAST_FILTER:
		dbgfs_bf->bf_temp_fast_filter = value;
		break;
	case MVM_DEBUGFS_BF_TEMP_SLOW_FILTER:
		dbgfs_bf->bf_temp_slow_filter = value;
		break;
	case MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER:
		dbgfs_bf->bf_enable_beacon_filter = value;
		break;
	case MVM_DEBUGFS_BF_DEBUG_FLAG:
		dbgfs_bf->bf_debug_flag = value;
		break;
	case MVM_DEBUGFS_BF_ESCAPE_TIMER:
		dbgfs_bf->bf_escape_timer = value;
		break;
	case MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT:
		dbgfs_bf->ba_enable_beacon_abort = value;
		break;
	case MVM_DEBUGFS_BA_ESCAPE_TIMER:
		dbgfs_bf->ba_escape_timer = value;
		break;
	}
}