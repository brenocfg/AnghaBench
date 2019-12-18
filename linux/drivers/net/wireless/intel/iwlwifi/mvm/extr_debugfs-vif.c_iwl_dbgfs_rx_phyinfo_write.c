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
typedef  size_t u16 ;
struct iwl_mvm_vif {struct iwl_mvm* mvm; } ;
struct iwl_mvm_phy_ctxt {int dummy; } ;
struct iwl_mvm {size_t dbgfs_rx_phyinfo; int /*<<< orphan*/  mutex; struct iwl_mvm_phy_ctxt* phy_ctxts; } ;
struct ieee80211_vif {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_chanctx_conf {int /*<<< orphan*/  rx_chains_dynamic; int /*<<< orphan*/  rx_chains_static; int /*<<< orphan*/  min_def; scalar_t__ drv_priv; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int iwl_mvm_phy_ctxt_changed (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int kstrtou16 (char*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static ssize_t iwl_dbgfs_rx_phyinfo_write(struct ieee80211_vif *vif, char *buf,
					  size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct iwl_mvm_phy_ctxt *phy_ctxt;
	u16 value;
	int ret;

	ret = kstrtou16(buf, 0, &value);
	if (ret)
		return ret;

	mutex_lock(&mvm->mutex);
	rcu_read_lock();

	chanctx_conf = rcu_dereference(vif->chanctx_conf);
	/* make sure the channel context is assigned */
	if (!chanctx_conf) {
		rcu_read_unlock();
		mutex_unlock(&mvm->mutex);
		return -EINVAL;
	}

	phy_ctxt = &mvm->phy_ctxts[*(u16 *)chanctx_conf->drv_priv];
	rcu_read_unlock();

	mvm->dbgfs_rx_phyinfo = value;

	ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, &chanctx_conf->min_def,
				       chanctx_conf->rx_chains_static,
				       chanctx_conf->rx_chains_dynamic);
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}