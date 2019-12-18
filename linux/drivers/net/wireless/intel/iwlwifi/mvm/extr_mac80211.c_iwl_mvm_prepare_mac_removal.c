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
struct iwl_mvm {int /*<<< orphan*/  roc_done_wk; } ;
struct ieee80211_vif {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_prepare_mac_removal(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif)
{
	if (vif->type == NL80211_IFTYPE_P2P_DEVICE) {
		/*
		 * Flush the ROC worker which will flush the OFFCHANNEL queue.
		 * We assume here that all the packets sent to the OFFCHANNEL
		 * queue are sent in ROC session.
		 */
		flush_work(&mvm->roc_done_wk);
	}
}