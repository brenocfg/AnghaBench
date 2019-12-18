#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ftm_responder; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_ftm_start_responder (struct iwl_mvm*,struct ieee80211_vif*) ; 

void iwl_mvm_ftm_restart_responder(struct iwl_mvm *mvm,
				   struct ieee80211_vif *vif)
{
	if (!vif->bss_conf.ftm_responder)
		return;

	iwl_mvm_ftm_start_responder(mvm, vif);
}