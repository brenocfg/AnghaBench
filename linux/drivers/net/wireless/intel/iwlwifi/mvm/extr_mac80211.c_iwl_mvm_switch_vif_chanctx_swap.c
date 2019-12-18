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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif_chanctx_switch {int /*<<< orphan*/  old_ctx; int /*<<< orphan*/  vif; int /*<<< orphan*/  new_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int __iwl_mvm_add_chanctx (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int __iwl_mvm_assign_vif_chanctx (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __iwl_mvm_remove_chanctx (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __iwl_mvm_unassign_vif_chanctx (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_mvm_nic_restart (struct iwl_mvm*,int) ; 
 int iwl_mvm_phy_ctx_count (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_teardown_tdls_peers (struct iwl_mvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iwl_mvm_switch_vif_chanctx_swap(struct iwl_mvm *mvm,
				struct ieee80211_vif_chanctx_switch *vifs)
{
	int ret;

	mutex_lock(&mvm->mutex);
	__iwl_mvm_unassign_vif_chanctx(mvm, vifs[0].vif, vifs[0].old_ctx, true);
	__iwl_mvm_remove_chanctx(mvm, vifs[0].old_ctx);

	ret = __iwl_mvm_add_chanctx(mvm, vifs[0].new_ctx);
	if (ret) {
		IWL_ERR(mvm, "failed to add new_ctx during channel switch\n");
		goto out_reassign;
	}

	ret = __iwl_mvm_assign_vif_chanctx(mvm, vifs[0].vif, vifs[0].new_ctx,
					   true);
	if (ret) {
		IWL_ERR(mvm,
			"failed to assign new_ctx during channel switch\n");
		goto out_remove;
	}

	/* we don't support TDLS during DCM - can be caused by channel switch */
	if (iwl_mvm_phy_ctx_count(mvm) > 1)
		iwl_mvm_teardown_tdls_peers(mvm);

	goto out;

out_remove:
	__iwl_mvm_remove_chanctx(mvm, vifs[0].new_ctx);

out_reassign:
	if (__iwl_mvm_add_chanctx(mvm, vifs[0].old_ctx)) {
		IWL_ERR(mvm, "failed to add old_ctx back after failure.\n");
		goto out_restart;
	}

	if (__iwl_mvm_assign_vif_chanctx(mvm, vifs[0].vif, vifs[0].old_ctx,
					 true)) {
		IWL_ERR(mvm, "failed to reassign old_ctx after failure.\n");
		goto out_restart;
	}

	goto out;

out_restart:
	/* things keep failing, better restart the hw */
	iwl_mvm_nic_restart(mvm, false);

out:
	mutex_unlock(&mvm->mutex);

	return ret;
}