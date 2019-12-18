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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_ftm_responder_iter_data {scalar_t__ ctx; int responder; } ;
struct TYPE_2__ {scalar_t__ ftmr_params; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_ftm_responder_chanctx_iter(void *_data, u8 *mac,
					       struct ieee80211_vif *vif)
{
	struct iwl_mvm_ftm_responder_iter_data *data = _data;

	if (rcu_access_pointer(vif->chanctx_conf) == data->ctx &&
	    vif->type == NL80211_IFTYPE_AP && vif->bss_conf.ftmr_params)
		data->responder = true;
}