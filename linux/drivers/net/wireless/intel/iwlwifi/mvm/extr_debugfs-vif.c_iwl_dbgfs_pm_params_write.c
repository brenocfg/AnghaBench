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
typedef  enum iwl_dbgfs_pm_mask { ____Placeholder_iwl_dbgfs_pm_mask } iwl_dbgfs_pm_mask ;

/* Variables and functions */
 size_t EINVAL ; 
 int MVM_DEBUGFS_PM_KEEP_ALIVE ; 
 int MVM_DEBUGFS_PM_LPRX_ENA ; 
 int MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD ; 
 int MVM_DEBUGFS_PM_RX_DATA_TIMEOUT ; 
 int MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS ; 
 int MVM_DEBUGFS_PM_SKIP_OVER_DTIM ; 
 int MVM_DEBUGFS_PM_SNOOZE_ENABLE ; 
 int MVM_DEBUGFS_PM_TX_DATA_TIMEOUT ; 
 int MVM_DEBUGFS_PM_UAPSD_MISBEHAVING ; 
 int MVM_DEBUGFS_PM_USE_PS_POLL ; 
 int POWER_LPRX_RSSI_THRESHOLD_MAX ; 
 int POWER_LPRX_RSSI_THRESHOLD_MIN ; 
 int /*<<< orphan*/  iwl_dbgfs_update_pm (struct iwl_mvm*,struct ieee80211_vif*,int,int) ; 
 int iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_pm_params_write(struct ieee80211_vif *vif, char *buf,
					 size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	enum iwl_dbgfs_pm_mask param;
	int val, ret;

	if (!strncmp("keep_alive=", buf, 11)) {
		if (sscanf(buf + 11, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_KEEP_ALIVE;
	} else if (!strncmp("skip_over_dtim=", buf, 15)) {
		if (sscanf(buf + 15, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_SKIP_OVER_DTIM;
	} else if (!strncmp("skip_dtim_periods=", buf, 18)) {
		if (sscanf(buf + 18, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS;
	} else if (!strncmp("rx_data_timeout=", buf, 16)) {
		if (sscanf(buf + 16, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_RX_DATA_TIMEOUT;
	} else if (!strncmp("tx_data_timeout=", buf, 16)) {
		if (sscanf(buf + 16, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_TX_DATA_TIMEOUT;
	} else if (!strncmp("lprx=", buf, 5)) {
		if (sscanf(buf + 5, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_LPRX_ENA;
	} else if (!strncmp("lprx_rssi_threshold=", buf, 20)) {
		if (sscanf(buf + 20, "%d", &val) != 1)
			return -EINVAL;
		if (val > POWER_LPRX_RSSI_THRESHOLD_MAX || val <
		    POWER_LPRX_RSSI_THRESHOLD_MIN)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD;
	} else if (!strncmp("snooze_enable=", buf, 14)) {
		if (sscanf(buf + 14, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_SNOOZE_ENABLE;
	} else if (!strncmp("uapsd_misbehaving=", buf, 18)) {
		if (sscanf(buf + 18, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_UAPSD_MISBEHAVING;
	} else if (!strncmp("use_ps_poll=", buf, 12)) {
		if (sscanf(buf + 12, "%d", &val) != 1)
			return -EINVAL;
		param = MVM_DEBUGFS_PM_USE_PS_POLL;
	} else {
		return -EINVAL;
	}

	mutex_lock(&mvm->mutex);
	iwl_dbgfs_update_pm(mvm, vif, param, val);
	ret = iwl_mvm_power_update_mac(mvm);
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}