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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct iwl_scale_tbl_info {int* expected_tpt; TYPE_2__ rate; TYPE_1__* win; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {size_t active_tbl; int last_tpt; struct iwl_scale_tbl_info* lq_info; } ;
typedef  size_t s8 ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {scalar_t__ success_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,int,int,...) ; 
 int IWL_INVALID_VALUE ; 
 int /*<<< orphan*/  IWL_MVM_RS_SR_NO_DECREASE ; 
 int IWL_RATE_INVALID ; 
 scalar_t__ RS_PERCENT (int /*<<< orphan*/ ) ; 
 int find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int rs_get_adjacent_rate (struct iwl_mvm*,int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 rs_get_best_rate(struct iwl_mvm *mvm,
			    struct iwl_lq_sta *lq_sta,
			    struct iwl_scale_tbl_info *tbl,	/* "search" */
			    unsigned long rate_mask, s8 index)
{
	struct iwl_scale_tbl_info *active_tbl =
	    &(lq_sta->lq_info[lq_sta->active_tbl]);
	s32 success_ratio = active_tbl->win[index].success_ratio;
	u16 expected_current_tpt = active_tbl->expected_tpt[index];
	const u16 *tpt_tbl = tbl->expected_tpt;
	u16 high_low;
	u32 target_tpt;
	int rate_idx;

	if (success_ratio >= RS_PERCENT(IWL_MVM_RS_SR_NO_DECREASE)) {
		target_tpt = 100 * expected_current_tpt;
		IWL_DEBUG_RATE(mvm,
			       "SR %d high. Find rate exceeding EXPECTED_CURRENT %d\n",
			       success_ratio, target_tpt);
	} else {
		target_tpt = lq_sta->last_tpt;
		IWL_DEBUG_RATE(mvm,
			       "SR %d not that good. Find rate exceeding ACTUAL_TPT %d\n",
			       success_ratio, target_tpt);
	}

	rate_idx = find_first_bit(&rate_mask, BITS_PER_LONG);

	while (rate_idx != IWL_RATE_INVALID) {
		if (target_tpt < (100 * tpt_tbl[rate_idx]))
			break;

		high_low = rs_get_adjacent_rate(mvm, rate_idx, rate_mask,
						tbl->rate.type);

		rate_idx = (high_low >> 8) & 0xff;
	}

	IWL_DEBUG_RATE(mvm, "Best rate found %d target_tp %d expected_new %d\n",
		       rate_idx, target_tpt,
		       rate_idx != IWL_RATE_INVALID ?
		       100 * tpt_tbl[rate_idx] : IWL_INVALID_VALUE);

	return rate_idx;
}