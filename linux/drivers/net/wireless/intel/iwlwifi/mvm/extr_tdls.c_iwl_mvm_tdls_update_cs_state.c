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
struct TYPE_3__ {int /*<<< orphan*/  sent_timestamp; } ;
struct TYPE_4__ {int state; int /*<<< orphan*/  cur_sta_id; TYPE_1__ peer; } ;
struct iwl_mvm {TYPE_2__ tdls_cs; } ;
typedef  enum iwl_mvm_tdls_cs_state { ____Placeholder_iwl_mvm_tdls_cs_state } iwl_mvm_tdls_cs_state ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TDLS (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_MVM_INVALID_STA ; 
 int IWL_MVM_TDLS_SW_IDLE ; 
 int IWL_MVM_TDLS_SW_REQ_SENT ; 
 int /*<<< orphan*/  iwl_mvm_get_systime (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_tdls_cs_state_str (int) ; 

__attribute__((used)) static void iwl_mvm_tdls_update_cs_state(struct iwl_mvm *mvm,
					 enum iwl_mvm_tdls_cs_state state)
{
	if (mvm->tdls_cs.state == state)
		return;

	IWL_DEBUG_TDLS(mvm, "TDLS channel switch state: %s -> %s\n",
		       iwl_mvm_tdls_cs_state_str(mvm->tdls_cs.state),
		       iwl_mvm_tdls_cs_state_str(state));
	mvm->tdls_cs.state = state;

	/* we only send requests to our switching peer - update sent time */
	if (state == IWL_MVM_TDLS_SW_REQ_SENT)
		mvm->tdls_cs.peer.sent_timestamp = iwl_mvm_get_systime(mvm);

	if (state == IWL_MVM_TDLS_SW_IDLE)
		mvm->tdls_cs.cur_sta_id = IWL_MVM_INVALID_STA;
}