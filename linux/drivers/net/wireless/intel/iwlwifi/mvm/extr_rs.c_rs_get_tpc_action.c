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
struct iwl_mvm {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum tpc_action { ____Placeholder_tpc_action } tpc_action ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*) ; 
 int IWL_INVALID_VALUE ; 
 int /*<<< orphan*/  IWL_MVM_RS_TPC_SR_FORCE_INCREASE ; 
 int /*<<< orphan*/  IWL_MVM_RS_TPC_SR_NO_INCREASE ; 
 scalar_t__ RS_PERCENT (int /*<<< orphan*/ ) ; 
 int TPC_ACTION_DECREASE ; 
 int TPC_ACTION_INCREASE ; 
 int TPC_ACTION_NO_RESTIRCTION ; 
 int TPC_ACTION_STAY ; 
 int TPC_INVALID ; 

__attribute__((used)) static enum tpc_action rs_get_tpc_action(struct iwl_mvm *mvm,
					 s32 sr, int weak, int strong,
					 int current_tpt,
					 int weak_tpt, int strong_tpt)
{
	/* stay until we have valid tpt */
	if (current_tpt == IWL_INVALID_VALUE) {
		IWL_DEBUG_RATE(mvm, "no current tpt. stay.\n");
		return TPC_ACTION_STAY;
	}

	/* Too many failures, increase txp */
	if (sr <= RS_PERCENT(IWL_MVM_RS_TPC_SR_FORCE_INCREASE) ||
	    current_tpt == 0) {
		IWL_DEBUG_RATE(mvm, "increase txp because of weak SR\n");
		return TPC_ACTION_NO_RESTIRCTION;
	}

	/* try decreasing first if applicable */
	if (sr >= RS_PERCENT(IWL_MVM_RS_TPC_SR_NO_INCREASE) &&
	    weak != TPC_INVALID) {
		if (weak_tpt == IWL_INVALID_VALUE &&
		    (strong_tpt == IWL_INVALID_VALUE ||
		     current_tpt >= strong_tpt)) {
			IWL_DEBUG_RATE(mvm,
				       "no weak txp measurement. decrease txp\n");
			return TPC_ACTION_DECREASE;
		}

		if (weak_tpt > current_tpt) {
			IWL_DEBUG_RATE(mvm,
				       "lower txp has better tpt. decrease txp\n");
			return TPC_ACTION_DECREASE;
		}
	}

	/* next, increase if needed */
	if (sr < RS_PERCENT(IWL_MVM_RS_TPC_SR_NO_INCREASE) &&
	    strong != TPC_INVALID) {
		if (weak_tpt == IWL_INVALID_VALUE &&
		    strong_tpt != IWL_INVALID_VALUE &&
		    current_tpt < strong_tpt) {
			IWL_DEBUG_RATE(mvm,
				       "higher txp has better tpt. increase txp\n");
			return TPC_ACTION_INCREASE;
		}

		if (weak_tpt < current_tpt &&
		    (strong_tpt == IWL_INVALID_VALUE ||
		     strong_tpt > current_tpt)) {
			IWL_DEBUG_RATE(mvm,
				       "lower txp has worse tpt. increase txp\n");
			return TPC_ACTION_INCREASE;
		}
	}

	IWL_DEBUG_RATE(mvm, "no need to increase or decrease txp - stay\n");
	return TPC_ACTION_STAY;
}