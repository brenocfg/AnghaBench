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
struct iwl_mvm_scan_params {void* type; void* hb_type; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 void* iwl_mvm_get_scan_type (struct iwl_mvm*,struct ieee80211_vif*) ; 
 void* iwl_mvm_get_scan_type_band (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_is_cdb_supported (struct iwl_mvm*) ; 

__attribute__((used)) static void iwl_mvm_fill_scan_type(struct iwl_mvm *mvm,
				   struct iwl_mvm_scan_params *params,
				   struct ieee80211_vif *vif)
{
	if (iwl_mvm_is_cdb_supported(mvm)) {
		params->type =
			iwl_mvm_get_scan_type_band(mvm, vif,
						   NL80211_BAND_2GHZ);
		params->hb_type =
			iwl_mvm_get_scan_type_band(mvm, vif,
						   NL80211_BAND_5GHZ);
	} else {
		params->type = iwl_mvm_get_scan_type(mvm, vif);
	}
}