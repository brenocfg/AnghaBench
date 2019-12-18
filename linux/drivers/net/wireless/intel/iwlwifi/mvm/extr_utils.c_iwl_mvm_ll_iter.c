#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_vif {TYPE_2__* phy_ctxt; } ;
struct iwl_mvm_low_latency_iter {int result; int* result_per_band; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {int band; } ;

/* Variables and functions */
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 scalar_t__ iwl_mvm_vif_low_latency (struct iwl_mvm_vif*) ; 

__attribute__((used)) static void iwl_mvm_ll_iter(void *_data, u8 *mac, struct ieee80211_vif *vif)
{
	struct iwl_mvm_low_latency_iter *result = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	enum nl80211_band band;

	if (iwl_mvm_vif_low_latency(mvmvif)) {
		result->result = true;

		if (!mvmvif->phy_ctxt)
			return;

		band = mvmvif->phy_ctxt->channel->band;
		result->result_per_band[band] = true;
	}
}