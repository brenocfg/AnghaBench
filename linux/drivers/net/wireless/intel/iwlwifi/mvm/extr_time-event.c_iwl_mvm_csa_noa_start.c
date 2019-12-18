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
struct iwl_mvm {int /*<<< orphan*/  csa_vif; } ;
struct ieee80211_vif {int /*<<< orphan*/  csa_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TE (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_csa_finish (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ieee80211_csa_is_complete (struct ieee80211_vif*) ; 
 struct ieee80211_vif* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void iwl_mvm_csa_noa_start(struct iwl_mvm *mvm)
{
	struct ieee80211_vif *csa_vif;

	rcu_read_lock();

	csa_vif = rcu_dereference(mvm->csa_vif);
	if (!csa_vif || !csa_vif->csa_active)
		goto out_unlock;

	IWL_DEBUG_TE(mvm, "CSA NOA started\n");

	/*
	 * CSA NoA is started but we still have beacons to
	 * transmit on the current channel.
	 * So we just do nothing here and the switch
	 * will be performed on the last TBTT.
	 */
	if (!ieee80211_csa_is_complete(csa_vif)) {
		IWL_WARN(mvm, "CSA NOA started too early\n");
		goto out_unlock;
	}

	ieee80211_csa_finish(csa_vif);

	rcu_read_unlock();

	RCU_INIT_POINTER(mvm->csa_vif, NULL);

	return;

out_unlock:
	rcu_read_unlock();
}