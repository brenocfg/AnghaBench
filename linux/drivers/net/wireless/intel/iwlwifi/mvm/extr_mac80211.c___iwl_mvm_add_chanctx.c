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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct cfg80211_chan_def {int dummy; } ;
struct ieee80211_chanctx_conf {int /*<<< orphan*/  rx_chains_dynamic; int /*<<< orphan*/  rx_chains_static; struct cfg80211_chan_def min_def; struct cfg80211_chan_def def; scalar_t__ drv_priv; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 struct iwl_mvm_phy_ctxt* iwl_mvm_get_free_phy_ctxt (struct iwl_mvm*) ; 
 int iwl_mvm_is_ftm_responder_chanctx (struct iwl_mvm*,struct ieee80211_chanctx_conf*) ; 
 int iwl_mvm_phy_ctxt_changed (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,struct cfg80211_chan_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_ref (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __iwl_mvm_add_chanctx(struct iwl_mvm *mvm,
				 struct ieee80211_chanctx_conf *ctx)
{
	u16 *phy_ctxt_id = (u16 *)ctx->drv_priv;
	struct iwl_mvm_phy_ctxt *phy_ctxt;
	bool responder = iwl_mvm_is_ftm_responder_chanctx(mvm, ctx);
	struct cfg80211_chan_def *def = responder ? &ctx->def : &ctx->min_def;
	int ret;

	lockdep_assert_held(&mvm->mutex);

	IWL_DEBUG_MAC80211(mvm, "Add channel context\n");

	phy_ctxt = iwl_mvm_get_free_phy_ctxt(mvm);
	if (!phy_ctxt) {
		ret = -ENOSPC;
		goto out;
	}

	ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, def,
				       ctx->rx_chains_static,
				       ctx->rx_chains_dynamic);
	if (ret) {
		IWL_ERR(mvm, "Failed to add PHY context\n");
		goto out;
	}

	iwl_mvm_phy_ctxt_ref(mvm, phy_ctxt);
	*phy_ctxt_id = phy_ctxt->id;
out:
	return ret;
}