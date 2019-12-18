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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_vif {size_t id; TYPE_2__* phy_ctxt; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_tcm_iterator(void *_data, u8 *mac,
				 struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u32 *band = _data;

	if (!mvmvif->phy_ctxt)
		return;

	band[mvmvif->id] = mvmvif->phy_ctxt->channel->band;
}