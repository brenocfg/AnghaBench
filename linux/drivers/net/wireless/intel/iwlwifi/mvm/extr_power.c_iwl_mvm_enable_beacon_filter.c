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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct iwl_beacon_filter_cmd {int /*<<< orphan*/  bf_enable_beacon_filter; int /*<<< orphan*/  member_0; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_BF_CMD_CONFIG_DEFAULTS ; 
 int _iwl_mvm_enable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_beacon_filter_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

int iwl_mvm_enable_beacon_filter(struct iwl_mvm *mvm,
				 struct ieee80211_vif *vif,
				 u32 flags)
{
	struct iwl_beacon_filter_cmd cmd = {
		IWL_BF_CMD_CONFIG_DEFAULTS,
		.bf_enable_beacon_filter = cpu_to_le32(1),
	};

	return _iwl_mvm_enable_beacon_filter(mvm, vif, &cmd, flags);
}