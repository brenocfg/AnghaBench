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
typedef  int u32 ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int iwl_mvm_get_tx_ant (struct iwl_mvm*,struct ieee80211_tx_info*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_get_tx_rate (struct iwl_mvm*,struct ieee80211_tx_info*,struct ieee80211_sta*) ; 

__attribute__((used)) static u32 iwl_mvm_get_tx_rate_n_flags(struct iwl_mvm *mvm,
				       struct ieee80211_tx_info *info,
				       struct ieee80211_sta *sta, __le16 fc)
{
	return iwl_mvm_get_tx_rate(mvm, info, sta) |
		iwl_mvm_get_tx_ant(mvm, info, sta, fc);
}