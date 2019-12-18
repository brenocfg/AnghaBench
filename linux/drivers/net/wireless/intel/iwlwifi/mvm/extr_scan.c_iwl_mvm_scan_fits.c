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
struct iwl_mvm {TYPE_2__* fw; } ;
struct ieee80211_scan_ies {scalar_t__ common_ie_len; scalar_t__* len; } ;
struct TYPE_3__ {int n_scan_channels; } ;
struct TYPE_4__ {TYPE_1__ ucode_capa; } ;

/* Variables and functions */
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int PROBE_OPTION_MAX ; 
 scalar_t__ iwl_mvm_max_scan_ie_fw_cmd_room (struct iwl_mvm*) ; 

__attribute__((used)) static inline bool iwl_mvm_scan_fits(struct iwl_mvm *mvm, int n_ssids,
				     struct ieee80211_scan_ies *ies,
				     int n_channels)
{
	return ((n_ssids <= PROBE_OPTION_MAX) &&
		(n_channels <= mvm->fw->ucode_capa.n_scan_channels) &
		(ies->common_ie_len +
		 ies->len[NL80211_BAND_2GHZ] +
		 ies->len[NL80211_BAND_5GHZ] <=
		 iwl_mvm_max_scan_ie_fw_cmd_room(mvm)));
}