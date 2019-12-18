#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm_vif {int he_ru_2mhz_block; } ;
struct iwl_mvm_he_obss_narrow_bw_ru_data {int tolerated; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct TYPE_5__ {TYPE_3__ chandef; } ;
struct ieee80211_vif {TYPE_2__ bss_conf; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  cfg80211_bss_iter (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,struct iwl_mvm_he_obss_narrow_bw_ru_data*) ; 
 int /*<<< orphan*/  iwl_mvm_check_he_obss_narrow_bw_ru_iter ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_check_he_obss_narrow_bw_ru(struct ieee80211_hw *hw,
					       struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_he_obss_narrow_bw_ru_data iter_data = {
		.tolerated = true,
	};

	if (!(vif->bss_conf.chandef.chan->flags & IEEE80211_CHAN_RADAR)) {
		mvmvif->he_ru_2mhz_block = false;
		return;
	}

	cfg80211_bss_iter(hw->wiphy, &vif->bss_conf.chandef,
			  iwl_mvm_check_he_obss_narrow_bw_ru_iter,
			  &iter_data);

	/*
	 * If there is at least one AP on radar channel that cannot
	 * tolerate 26-tone RU UL OFDMA transmissions using HE TB PPDU.
	 */
	mvmvif->he_ru_2mhz_block = !iter_data.tolerated;
}