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
struct iwl_scale_tbl_info {int* expected_tpt; } ;
struct iwl_mvm {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum rs_action { ____Placeholder_rs_action } rs_action ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*) ; 
 int IWL_INVALID_VALUE ; 
 int /*<<< orphan*/  IWL_MVM_RS_SR_FORCE_DECREASE ; 
 int /*<<< orphan*/  IWL_MVM_RS_SR_NO_DECREASE ; 
 int IWL_RATE_INVALID ; 
 int RS_ACTION_DOWNSCALE ; 
 int RS_ACTION_STAY ; 
 int RS_ACTION_UPSCALE ; 
 scalar_t__ RS_PERCENT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum rs_action rs_get_rate_action(struct iwl_mvm *mvm,
					 struct iwl_scale_tbl_info *tbl,
					 s32 sr, int low, int high,
					 int current_tpt,
					 int low_tpt, int high_tpt)
{
	enum rs_action action = RS_ACTION_STAY;

	if ((sr <= RS_PERCENT(IWL_MVM_RS_SR_FORCE_DECREASE)) ||
	    (current_tpt == 0)) {
		IWL_DEBUG_RATE(mvm,
			       "Decrease rate because of low SR\n");
		return RS_ACTION_DOWNSCALE;
	}

	if ((low_tpt == IWL_INVALID_VALUE) &&
	    (high_tpt == IWL_INVALID_VALUE) &&
	    (high != IWL_RATE_INVALID)) {
		IWL_DEBUG_RATE(mvm,
			       "No data about high/low rates. Increase rate\n");
		return RS_ACTION_UPSCALE;
	}

	if ((high_tpt == IWL_INVALID_VALUE) &&
	    (high != IWL_RATE_INVALID) &&
	    (low_tpt != IWL_INVALID_VALUE) &&
	    (low_tpt < current_tpt)) {
		IWL_DEBUG_RATE(mvm,
			       "No data about high rate and low rate is worse. Increase rate\n");
		return RS_ACTION_UPSCALE;
	}

	if ((high_tpt != IWL_INVALID_VALUE) &&
	    (high_tpt > current_tpt)) {
		IWL_DEBUG_RATE(mvm,
			       "Higher rate is better. Increate rate\n");
		return RS_ACTION_UPSCALE;
	}

	if ((low_tpt != IWL_INVALID_VALUE) &&
	    (high_tpt != IWL_INVALID_VALUE) &&
	    (low_tpt < current_tpt) &&
	    (high_tpt < current_tpt)) {
		IWL_DEBUG_RATE(mvm,
			       "Both high and low are worse. Maintain rate\n");
		return RS_ACTION_STAY;
	}

	if ((low_tpt != IWL_INVALID_VALUE) &&
	    (low_tpt > current_tpt)) {
		IWL_DEBUG_RATE(mvm,
			       "Lower rate is better\n");
		action = RS_ACTION_DOWNSCALE;
		goto out;
	}

	if ((low_tpt == IWL_INVALID_VALUE) &&
	    (low != IWL_RATE_INVALID)) {
		IWL_DEBUG_RATE(mvm,
			       "No data about lower rate\n");
		action = RS_ACTION_DOWNSCALE;
		goto out;
	}

	IWL_DEBUG_RATE(mvm, "Maintain rate\n");

out:
	if ((action == RS_ACTION_DOWNSCALE) && (low != IWL_RATE_INVALID)) {
		if (sr >= RS_PERCENT(IWL_MVM_RS_SR_NO_DECREASE)) {
			IWL_DEBUG_RATE(mvm,
				       "SR is above NO DECREASE. Avoid downscale\n");
			action = RS_ACTION_STAY;
		} else if (current_tpt > (100 * tbl->expected_tpt[low])) {
			IWL_DEBUG_RATE(mvm,
				       "Current TPT is higher than max expected in low rate. Avoid downscale\n");
			action = RS_ACTION_STAY;
		} else {
			IWL_DEBUG_RATE(mvm, "Decrease rate\n");
		}
	}

	return action;
}