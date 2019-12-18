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
typedef  int u16 ;
struct iwl_mvm_vif {int dbgfs_quota_min; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw; } ;
struct ieee80211_vif {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  ieee80211_iterate_interfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iwl_dbgfs_quota_check ; 
 int /*<<< orphan*/  iwl_mvm_update_quotas (struct iwl_mvm*,int,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int kstrtou16 (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_quota_min_write(struct ieee80211_vif *vif, char *buf,
					 size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	u16 value;
	int ret;

	ret = kstrtou16(buf, 0, &value);
	if (ret)
		return ret;

	if (value > 95)
		return -EINVAL;

	mutex_lock(&mvm->mutex);

	mvmvif->dbgfs_quota_min = 0;
	ieee80211_iterate_interfaces(mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
				     iwl_dbgfs_quota_check, &ret);
	if (ret == 0) {
		mvmvif->dbgfs_quota_min = value;
		iwl_mvm_update_quotas(mvm, false, NULL);
	}
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}