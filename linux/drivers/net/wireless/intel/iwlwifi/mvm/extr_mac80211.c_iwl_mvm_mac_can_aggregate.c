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
struct sk_buff {scalar_t__ protocol; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_can_hw_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  iwl_mvm_is_csum_supported (struct iwl_mvm*) ; 

__attribute__((used)) static bool iwl_mvm_mac_can_aggregate(struct ieee80211_hw *hw,
				      struct sk_buff *head,
				      struct sk_buff *skb)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	/* For now don't aggregate IPv6 in AMSDU */
	if (skb->protocol != htons(ETH_P_IP))
		return false;

	if (!iwl_mvm_is_csum_supported(mvm))
		return true;

	return iwl_mvm_can_hw_csum(skb) == iwl_mvm_can_hw_csum(head);
}