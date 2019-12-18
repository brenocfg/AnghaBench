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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct rs_rate {int index; void* type; } ;
struct iwl_scale_tbl_info {struct rs_rate rate; struct iwl_rate_scale_data* win; int /*<<< orphan*/  expected_tpt; } ;
struct iwl_rate_scale_data {scalar_t__ counter; scalar_t__ success_counter; int average_tpt; int /*<<< orphan*/  success_ratio; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  agg_tids; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {size_t is_agg; int search_better_tbl; size_t active_tbl; int last_tpt; struct iwl_scale_tbl_info* lq_info; int /*<<< orphan*/  rs_state; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum rs_column { ____Placeholder_rs_column } rs_column ;
typedef  enum rs_action { ____Placeholder_rs_action } rs_action ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 void* IWL_INVALID_VALUE ; 
 scalar_t__ IWL_MVM_RS_80_20_FAR_RANGE_TWEAK ; 
 scalar_t__ IWL_MVM_RS_RATE_MIN_FAILURE_TH ; 
 scalar_t__ IWL_MVM_RS_RATE_MIN_SUCCESS_TH ; 
 int IWL_RATE_INVALID ; 
 void* LQ_NONE ; 
#define  RS_ACTION_DOWNSCALE 130 
#define  RS_ACTION_STAY 129 
#define  RS_ACTION_UPSCALE 128 
 int RS_COLUMN_INVALID ; 
 int /*<<< orphan*/  RS_STATE_SEARCH_CYCLE_ENDED ; 
 int /*<<< orphan*/  RS_STATE_SEARCH_CYCLE_STARTED ; 
 int /*<<< orphan*/  RS_STATE_STAY_IN_COLUMN ; 
 int /*<<< orphan*/  is_legacy (struct rs_rate*) ; 
 scalar_t__ is_mimo (struct rs_rate*) ; 
 int /*<<< orphan*/  iwl_mvm_bt_coex_is_mimo_allowed (struct iwl_mvm*,struct ieee80211_sta*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  rs_dump_rate (struct iwl_mvm*,struct rs_rate*,char*) ; 
 int rs_get_adjacent_rate (struct iwl_mvm*,int,int,void*) ; 
 int rs_get_next_column (struct iwl_mvm*,struct iwl_lq_sta*,struct ieee80211_sta*,struct iwl_scale_tbl_info*) ; 
 int rs_get_rate_action (struct iwl_mvm*,struct iwl_scale_tbl_info*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int rs_get_supported_rates (struct iwl_lq_sta*,struct rs_rate*) ; 
 int /*<<< orphan*/  rs_pretty_rate (struct rs_rate*) ; 
 int /*<<< orphan*/  rs_rate_scale_clear_tbl_windows (struct iwl_mvm*,struct iwl_scale_tbl_info*) ; 
 size_t rs_search_tbl (size_t) ; 
 int /*<<< orphan*/  rs_set_amsdu_len (struct iwl_mvm*,struct ieee80211_sta*,struct iwl_scale_tbl_info*,int) ; 
 int /*<<< orphan*/  rs_set_expected_tpt_table (struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 
 int /*<<< orphan*/  rs_set_stay_in_table (struct iwl_mvm*,int /*<<< orphan*/ ,struct iwl_lq_sta*) ; 
 int /*<<< orphan*/  rs_stay_in_table (struct iwl_lq_sta*,int) ; 
 int rs_switch_to_column (struct iwl_mvm*,struct iwl_lq_sta*,struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  rs_tl_turn_on_agg (struct iwl_mvm*,struct iwl_mvm_sta*,int,struct iwl_lq_sta*,struct ieee80211_sta*) ; 
 size_t rs_tpc_perform (struct iwl_mvm*,struct ieee80211_sta*,struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 
 int /*<<< orphan*/  rs_tweak_rate_tbl (struct iwl_mvm*,struct ieee80211_sta*,struct iwl_lq_sta*,struct iwl_scale_tbl_info*,int) ; 
 int /*<<< orphan*/  rs_update_rate_tbl (struct iwl_mvm*,struct ieee80211_sta*,struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 

__attribute__((used)) static void rs_rate_scale_perform(struct iwl_mvm *mvm,
				  struct ieee80211_sta *sta,
				  struct iwl_lq_sta *lq_sta,
				  int tid, bool ndp)
{
	int low = IWL_RATE_INVALID;
	int high = IWL_RATE_INVALID;
	int index;
	struct iwl_rate_scale_data *window = NULL;
	int current_tpt = IWL_INVALID_VALUE;
	int low_tpt = IWL_INVALID_VALUE;
	int high_tpt = IWL_INVALID_VALUE;
	u32 fail_count;
	enum rs_action scale_action = RS_ACTION_STAY;
	u16 rate_mask;
	u8 update_lq = 0;
	struct iwl_scale_tbl_info *tbl, *tbl1;
	u8 active_tbl = 0;
	u8 done_search = 0;
	u16 high_low;
	s32 sr;
	u8 prev_agg = lq_sta->is_agg;
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct rs_rate *rate;

	lq_sta->is_agg = !!mvmsta->agg_tids;

	/*
	 * Select rate-scale / modulation-mode table to work with in
	 * the rest of this function:  "search" if searching for better
	 * modulation mode, or "active" if doing rate scaling within a mode.
	 */
	if (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	else
		active_tbl = rs_search_tbl(lq_sta->active_tbl);

	tbl = &(lq_sta->lq_info[active_tbl]);
	rate = &tbl->rate;

	if (prev_agg != lq_sta->is_agg) {
		IWL_DEBUG_RATE(mvm,
			       "Aggregation changed: prev %d current %d. Update expected TPT table\n",
			       prev_agg, lq_sta->is_agg);
		rs_set_expected_tpt_table(lq_sta, tbl);
		rs_rate_scale_clear_tbl_windows(mvm, tbl);
	}

	/* current tx rate */
	index = rate->index;

	/* rates available for this association, and for modulation mode */
	rate_mask = rs_get_supported_rates(lq_sta, rate);

	if (!(BIT(index) & rate_mask)) {
		IWL_ERR(mvm, "Current Rate is not valid\n");
		if (lq_sta->search_better_tbl) {
			/* revert to active table if search table is not valid*/
			rate->type = LQ_NONE;
			lq_sta->search_better_tbl = 0;
			tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
			rs_update_rate_tbl(mvm, sta, lq_sta, tbl);
		}
		return;
	}

	/* Get expected throughput table and history window for current rate */
	if (!tbl->expected_tpt) {
		IWL_ERR(mvm, "tbl->expected_tpt is NULL\n");
		return;
	}

	/* TODO: handle rate_idx_mask and rate_idx_mcs_mask */
	window = &(tbl->win[index]);

	/*
	 * If there is not enough history to calculate actual average
	 * throughput, keep analyzing results of more tx frames, without
	 * changing rate or mode (bypass most of the rest of this function).
	 * Set up new rate table in uCode only if old rate is not supported
	 * in current association (use new rate found above).
	 */
	fail_count = window->counter - window->success_counter;
	if ((fail_count < IWL_MVM_RS_RATE_MIN_FAILURE_TH) &&
	    (window->success_counter < IWL_MVM_RS_RATE_MIN_SUCCESS_TH)) {
		IWL_DEBUG_RATE(mvm,
			       "%s: Test Window: succ %d total %d\n",
			       rs_pretty_rate(rate),
			       window->success_counter, window->counter);

		/* Can't calculate this yet; not enough history */
		window->average_tpt = IWL_INVALID_VALUE;

		/* Should we stay with this modulation mode,
		 * or search for a new one? */
		rs_stay_in_table(lq_sta, false);

		return;
	}

	/* If we are searching for better modulation mode, check success. */
	if (lq_sta->search_better_tbl) {
		/* If good success, continue using the "search" mode;
		 * no need to send new link quality command, since we're
		 * continuing to use the setup that we've been trying. */
		if (window->average_tpt > lq_sta->last_tpt) {
			IWL_DEBUG_RATE(mvm,
				       "SWITCHING TO NEW TABLE SR: %d "
				       "cur-tpt %d old-tpt %d\n",
				       window->success_ratio,
				       window->average_tpt,
				       lq_sta->last_tpt);

			/* Swap tables; "search" becomes "active" */
			lq_sta->active_tbl = active_tbl;
			current_tpt = window->average_tpt;
		/* Else poor success; go back to mode in "active" table */
		} else {
			IWL_DEBUG_RATE(mvm,
				       "GOING BACK TO THE OLD TABLE: SR %d "
				       "cur-tpt %d old-tpt %d\n",
				       window->success_ratio,
				       window->average_tpt,
				       lq_sta->last_tpt);

			/* Nullify "search" table */
			rate->type = LQ_NONE;

			/* Revert to "active" table */
			active_tbl = lq_sta->active_tbl;
			tbl = &(lq_sta->lq_info[active_tbl]);

			/* Revert to "active" rate and throughput info */
			index = tbl->rate.index;
			current_tpt = lq_sta->last_tpt;

			/* Need to set up a new rate table in uCode */
			update_lq = 1;
		}

		/* Either way, we've made a decision; modulation mode
		 * search is done, allow rate adjustment next time. */
		lq_sta->search_better_tbl = 0;
		done_search = 1;	/* Don't switch modes below! */
		goto lq_update;
	}

	/* (Else) not in search of better modulation mode, try for better
	 * starting rate, while staying in this mode. */
	high_low = rs_get_adjacent_rate(mvm, index, rate_mask, rate->type);
	low = high_low & 0xff;
	high = (high_low >> 8) & 0xff;

	/* TODO: handle rate_idx_mask and rate_idx_mcs_mask */

	sr = window->success_ratio;

	/* Collect measured throughputs for current and adjacent rates */
	current_tpt = window->average_tpt;
	if (low != IWL_RATE_INVALID)
		low_tpt = tbl->win[low].average_tpt;
	if (high != IWL_RATE_INVALID)
		high_tpt = tbl->win[high].average_tpt;

	IWL_DEBUG_RATE(mvm,
		       "%s: cur_tpt %d SR %d low %d high %d low_tpt %d high_tpt %d\n",
		       rs_pretty_rate(rate), current_tpt, sr,
		       low, high, low_tpt, high_tpt);

	scale_action = rs_get_rate_action(mvm, tbl, sr, low, high,
					  current_tpt, low_tpt, high_tpt);

	/* Force a search in case BT doesn't like us being in MIMO */
	if (is_mimo(rate) &&
	    !iwl_mvm_bt_coex_is_mimo_allowed(mvm, sta)) {
		IWL_DEBUG_RATE(mvm,
			       "BT Coex forbids MIMO. Search for new config\n");
		rs_stay_in_table(lq_sta, true);
		goto lq_update;
	}

	switch (scale_action) {
	case RS_ACTION_DOWNSCALE:
		/* Decrease starting rate, update uCode's rate table */
		if (low != IWL_RATE_INVALID) {
			update_lq = 1;
			index = low;
		} else {
			IWL_DEBUG_RATE(mvm,
				       "At the bottom rate. Can't decrease\n");
		}

		break;
	case RS_ACTION_UPSCALE:
		/* Increase starting rate, update uCode's rate table */
		if (high != IWL_RATE_INVALID) {
			update_lq = 1;
			index = high;
		} else {
			IWL_DEBUG_RATE(mvm,
				       "At the top rate. Can't increase\n");
		}

		break;
	case RS_ACTION_STAY:
		/* No change */
		if (lq_sta->rs_state == RS_STATE_STAY_IN_COLUMN)
			update_lq = rs_tpc_perform(mvm, sta, lq_sta, tbl);
		break;
	default:
		break;
	}

lq_update:
	/* Replace uCode's rate table for the destination station. */
	if (update_lq) {
		tbl->rate.index = index;
		if (IWL_MVM_RS_80_20_FAR_RANGE_TWEAK)
			rs_tweak_rate_tbl(mvm, sta, lq_sta, tbl, scale_action);
		rs_set_amsdu_len(mvm, sta, tbl, scale_action);
		rs_update_rate_tbl(mvm, sta, lq_sta, tbl);
	}

	rs_stay_in_table(lq_sta, false);

	/*
	 * Search for new modulation mode if we're:
	 * 1)  Not changing rates right now
	 * 2)  Not just finishing up a search
	 * 3)  Allowing a new search
	 */
	if (!update_lq && !done_search &&
	    lq_sta->rs_state == RS_STATE_SEARCH_CYCLE_STARTED
	    && window->counter) {
		enum rs_column next_column;

		/* Save current throughput to compare with "search" throughput*/
		lq_sta->last_tpt = current_tpt;

		IWL_DEBUG_RATE(mvm,
			       "Start Search: update_lq %d done_search %d rs_state %d win->counter %d\n",
			       update_lq, done_search, lq_sta->rs_state,
			       window->counter);

		next_column = rs_get_next_column(mvm, lq_sta, sta, tbl);
		if (next_column != RS_COLUMN_INVALID) {
			int ret = rs_switch_to_column(mvm, lq_sta, sta,
						      next_column);
			if (!ret)
				lq_sta->search_better_tbl = 1;
		} else {
			IWL_DEBUG_RATE(mvm,
				       "No more columns to explore in search cycle. Go to RS_STATE_SEARCH_CYCLE_ENDED\n");
			lq_sta->rs_state = RS_STATE_SEARCH_CYCLE_ENDED;
		}

		/* If new "search" mode was selected, set up in uCode table */
		if (lq_sta->search_better_tbl) {
			/* Access the "search" table, clear its history. */
			tbl = &lq_sta->lq_info[rs_search_tbl(lq_sta->active_tbl)];
			rs_rate_scale_clear_tbl_windows(mvm, tbl);

			/* Use new "search" start rate */
			index = tbl->rate.index;

			rs_dump_rate(mvm, &tbl->rate,
				     "Switch to SEARCH TABLE:");
			rs_update_rate_tbl(mvm, sta, lq_sta, tbl);
		} else {
			done_search = 1;
		}
	}

	if (!ndp)
		rs_tl_turn_on_agg(mvm, mvmsta, tid, lq_sta, sta);

	if (done_search && lq_sta->rs_state == RS_STATE_SEARCH_CYCLE_ENDED) {
		tbl1 = &(lq_sta->lq_info[lq_sta->active_tbl]);
		rs_set_stay_in_table(mvm, is_legacy(&tbl1->rate), lq_sta);
	}
}