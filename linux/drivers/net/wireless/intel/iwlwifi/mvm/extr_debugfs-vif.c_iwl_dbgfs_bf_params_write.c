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
struct iwl_mvm_vif {struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum iwl_dbgfs_bf_mask { ____Placeholder_iwl_dbgfs_bf_mask } iwl_dbgfs_bf_mask ;

/* Variables and functions */
 size_t EINVAL ; 
 int IWL_BA_ESCAPE_TIMER_MAX ; 
 int IWL_BA_ESCAPE_TIMER_MIN ; 
 int IWL_BF_ENERGY_DELTA_MAX ; 
 int IWL_BF_ENERGY_DELTA_MIN ; 
 int IWL_BF_ESCAPE_TIMER_MAX ; 
 int IWL_BF_ESCAPE_TIMER_MIN ; 
 int IWL_BF_ROAMING_ENERGY_DELTA_MAX ; 
 int IWL_BF_ROAMING_ENERGY_DELTA_MIN ; 
 int IWL_BF_ROAMING_STATE_MAX ; 
 int IWL_BF_ROAMING_STATE_MIN ; 
 int IWL_BF_TEMP_FAST_FILTER_MAX ; 
 int IWL_BF_TEMP_FAST_FILTER_MIN ; 
 int IWL_BF_TEMP_SLOW_FILTER_MAX ; 
 int IWL_BF_TEMP_SLOW_FILTER_MIN ; 
 int IWL_BF_TEMP_THRESHOLD_MAX ; 
 int IWL_BF_TEMP_THRESHOLD_MIN ; 
 int MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT ; 
 int MVM_DEBUGFS_BA_ESCAPE_TIMER ; 
 int MVM_DEBUGFS_BF_DEBUG_FLAG ; 
 int MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER ; 
 int MVM_DEBUGFS_BF_ENERGY_DELTA ; 
 int MVM_DEBUGFS_BF_ESCAPE_TIMER ; 
 int MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA ; 
 int MVM_DEBUGFS_BF_ROAMING_STATE ; 
 int MVM_DEBUGFS_BF_TEMP_FAST_FILTER ; 
 int MVM_DEBUGFS_BF_TEMP_SLOW_FILTER ; 
 int MVM_DEBUGFS_BF_TEMP_THRESHOLD ; 
 int /*<<< orphan*/  iwl_dbgfs_update_bf (struct ieee80211_vif*,int,int) ; 
 int iwl_mvm_disable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_enable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_bf_params_write(struct ieee80211_vif *vif, char *buf,
					 size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	enum iwl_dbgfs_bf_mask param;
	int value, ret = 0;

	if (!strncmp("bf_energy_delta=", buf, 16)) {
		if (sscanf(buf+16, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BF_ENERGY_DELTA_MIN ||
		    value > IWL_BF_ENERGY_DELTA_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_ENERGY_DELTA;
	} else if (!strncmp("bf_roaming_energy_delta=", buf, 24)) {
		if (sscanf(buf+24, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BF_ROAMING_ENERGY_DELTA_MIN ||
		    value > IWL_BF_ROAMING_ENERGY_DELTA_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA;
	} else if (!strncmp("bf_roaming_state=", buf, 17)) {
		if (sscanf(buf+17, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BF_ROAMING_STATE_MIN ||
		    value > IWL_BF_ROAMING_STATE_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_ROAMING_STATE;
	} else if (!strncmp("bf_temp_threshold=", buf, 18)) {
		if (sscanf(buf+18, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BF_TEMP_THRESHOLD_MIN ||
		    value > IWL_BF_TEMP_THRESHOLD_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_TEMP_THRESHOLD;
	} else if (!strncmp("bf_temp_fast_filter=", buf, 20)) {
		if (sscanf(buf+20, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BF_TEMP_FAST_FILTER_MIN ||
		    value > IWL_BF_TEMP_FAST_FILTER_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_TEMP_FAST_FILTER;
	} else if (!strncmp("bf_temp_slow_filter=", buf, 20)) {
		if (sscanf(buf+20, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BF_TEMP_SLOW_FILTER_MIN ||
		    value > IWL_BF_TEMP_SLOW_FILTER_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_TEMP_SLOW_FILTER;
	} else if (!strncmp("bf_enable_beacon_filter=", buf, 24)) {
		if (sscanf(buf+24, "%d", &value) != 1)
			return -EINVAL;
		if (value < 0 || value > 1)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER;
	} else if (!strncmp("bf_debug_flag=", buf, 14)) {
		if (sscanf(buf+14, "%d", &value) != 1)
			return -EINVAL;
		if (value < 0 || value > 1)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_DEBUG_FLAG;
	} else if (!strncmp("bf_escape_timer=", buf, 16)) {
		if (sscanf(buf+16, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BF_ESCAPE_TIMER_MIN ||
		    value > IWL_BF_ESCAPE_TIMER_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BF_ESCAPE_TIMER;
	} else if (!strncmp("ba_escape_timer=", buf, 16)) {
		if (sscanf(buf+16, "%d", &value) != 1)
			return -EINVAL;
		if (value < IWL_BA_ESCAPE_TIMER_MIN ||
		    value > IWL_BA_ESCAPE_TIMER_MAX)
			return -EINVAL;
		param = MVM_DEBUGFS_BA_ESCAPE_TIMER;
	} else if (!strncmp("ba_enable_beacon_abort=", buf, 23)) {
		if (sscanf(buf+23, "%d", &value) != 1)
			return -EINVAL;
		if (value < 0 || value > 1)
			return -EINVAL;
		param = MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT;
	} else {
		return -EINVAL;
	}

	mutex_lock(&mvm->mutex);
	iwl_dbgfs_update_bf(vif, param, value);
	if (param == MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER && !value)
		ret = iwl_mvm_disable_beacon_filter(mvm, vif, 0);
	else
		ret = iwl_mvm_enable_beacon_filter(mvm, vif, 0);
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}