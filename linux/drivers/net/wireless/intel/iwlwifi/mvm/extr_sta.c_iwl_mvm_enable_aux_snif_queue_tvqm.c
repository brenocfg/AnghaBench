#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm {TYPE_3__* trans; } ;
struct TYPE_8__ {scalar_t__ tfd_q_hang_detect; } ;
struct TYPE_7__ {TYPE_2__* trans_cfg; } ;
struct TYPE_6__ {TYPE_1__* base_params; } ;
struct TYPE_5__ {unsigned int wd_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MAX_TID_COUNT ; 
 unsigned int IWL_WATCHDOG_DISABLED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_tvqm_enable_txq (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_4__ iwlmvm_mod_params ; 

__attribute__((used)) static int iwl_mvm_enable_aux_snif_queue_tvqm(struct iwl_mvm *mvm, u8 sta_id)
{
	unsigned int wdg_timeout = iwlmvm_mod_params.tfd_q_hang_detect ?
		mvm->trans->trans_cfg->base_params->wd_timeout :
		IWL_WATCHDOG_DISABLED;

	WARN_ON(!iwl_mvm_has_new_tx_api(mvm));

	return iwl_mvm_tvqm_enable_txq(mvm, sta_id, IWL_MAX_TID_COUNT,
				       wdg_timeout);
}