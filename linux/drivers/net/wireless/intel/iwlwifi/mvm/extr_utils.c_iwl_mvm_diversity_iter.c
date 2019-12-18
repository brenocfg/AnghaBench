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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_vif {scalar_t__* smps_requests; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_SMPS_DYNAMIC ; 
 scalar_t__ IEEE80211_SMPS_STATIC ; 
 int NUM_IWL_MVM_SMPS_REQ ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_diversity_iter(void *_data, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	bool *result = _data;
	int i;

	for (i = 0; i < NUM_IWL_MVM_SMPS_REQ; i++) {
		if (mvmvif->smps_requests[i] == IEEE80211_SMPS_STATIC ||
		    mvmvif->smps_requests[i] == IEEE80211_SMPS_DYNAMIC)
			*result = false;
	}
}