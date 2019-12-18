#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct iwl_mvm_vif {int /*<<< orphan*/  ap_ibss_active; } ;
struct iwl_mvm_phy_ctxt {int dummy; } ;
struct iwl_mvm {struct iwl_mvm_phy_ctxt* phy_ctxts; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  ftm_responder; struct ieee80211_ftm_responder_params* ftmr_params; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  chanctx_conf; scalar_t__ p2p; TYPE_1__ bss_conf; } ;
struct ieee80211_ftm_responder_params {int dummy; } ;
struct ieee80211_chanctx_conf {int /*<<< orphan*/  def; int /*<<< orphan*/  rx_chains_dynamic; int /*<<< orphan*/  rx_chains_static; scalar_t__ drv_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int iwl_mvm_ftm_responder_cmd (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ *) ; 
 int iwl_mvm_ftm_responder_dyn_cfg_cmd (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_ftm_responder_params*) ; 
 int iwl_mvm_phy_ctxt_changed (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int iwl_mvm_ftm_start_responder(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct ieee80211_ftm_responder_params *params;
	struct ieee80211_chanctx_conf ctx, *pctx;
	u16 *phy_ctxt_id;
	struct iwl_mvm_phy_ctxt *phy_ctxt;
	int ret;

	params = vif->bss_conf.ftmr_params;

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON_ONCE(!vif->bss_conf.ftm_responder))
		return -EINVAL;

	if (vif->p2p || vif->type != NL80211_IFTYPE_AP ||
	    !mvmvif->ap_ibss_active) {
		IWL_ERR(mvm, "Cannot start responder, not in AP mode\n");
		return -EIO;
	}

	rcu_read_lock();
	pctx = rcu_dereference(vif->chanctx_conf);
	/* Copy the ctx to unlock the rcu and send the phy ctxt. We don't care
	 * about changes in the ctx after releasing the lock because the driver
	 * is still protected by the mutex. */
	ctx = *pctx;
	phy_ctxt_id  = (u16 *)pctx->drv_priv;
	rcu_read_unlock();

	phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, &ctx.def,
				       ctx.rx_chains_static,
				       ctx.rx_chains_dynamic);
	if (ret)
		return ret;

	ret = iwl_mvm_ftm_responder_cmd(mvm, vif, &ctx.def);
	if (ret)
		return ret;

	if (params)
		ret = iwl_mvm_ftm_responder_dyn_cfg_cmd(mvm, vif, params);

	return ret;
}