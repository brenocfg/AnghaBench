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
typedef  size_t u8 ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * vif_id_to_mac; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_vif* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct ieee80211_vif* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ieee80211_vif *
iwl_mvm_rcu_dereference_vif_id(struct iwl_mvm *mvm, u8 vif_id, bool rcu)
{
	if (WARN_ON(vif_id >= ARRAY_SIZE(mvm->vif_id_to_mac)))
		return NULL;

	if (rcu)
		return rcu_dereference(mvm->vif_id_to_mac[vif_id]);

	return rcu_dereference_protected(mvm->vif_id_to_mac[vif_id],
					 lockdep_is_held(&mvm->mutex));
}