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
struct iwl_mvm_sta {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct iwl_mvm_sta *
iwl_mvm_sta_from_staid_rcu(struct iwl_mvm *mvm, u8 sta_id)
{
	struct ieee80211_sta *sta;

	if (sta_id >= ARRAY_SIZE(mvm->fw_id_to_mac_id))
		return NULL;

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);

	/* This can happen if the station has been removed right now */
	if (IS_ERR_OR_NULL(sta))
		return NULL;

	return iwl_mvm_sta_from_mac80211(sta);
}