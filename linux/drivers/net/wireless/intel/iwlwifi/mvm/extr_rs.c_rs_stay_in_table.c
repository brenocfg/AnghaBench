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
struct iwl_scale_tbl_info {int /*<<< orphan*/  column; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {struct iwl_mvm* drv; } ;
struct iwl_lq_sta {int active_tbl; scalar_t__ rs_state; scalar_t__ table_count; scalar_t__ table_count_limit; int /*<<< orphan*/  visited_columns; scalar_t__ flush_timer; int /*<<< orphan*/  total_success; int /*<<< orphan*/  total_failed; int /*<<< orphan*/  search_better_tbl; int /*<<< orphan*/  max_success_limit; int /*<<< orphan*/  max_failure_limit; struct iwl_scale_tbl_info* lq_info; TYPE_1__ pers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,...) ; 
 int IWL_MVM_RS_STAY_IN_COLUMN_TIMEOUT ; 
 scalar_t__ RS_STATE_SEARCH_CYCLE_STARTED ; 
 scalar_t__ RS_STATE_STAY_IN_COLUMN ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rs_rate_scale_clear_tbl_windows (struct iwl_mvm*,struct iwl_scale_tbl_info*) ; 
 int time_after (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void rs_stay_in_table(struct iwl_lq_sta *lq_sta, bool force_search)
{
	struct iwl_scale_tbl_info *tbl;
	int active_tbl;
	int flush_interval_passed = 0;
	struct iwl_mvm *mvm;

	mvm = lq_sta->pers.drv;
	active_tbl = lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	/* If we've been disallowing search, see if we should now allow it */
	if (lq_sta->rs_state == RS_STATE_STAY_IN_COLUMN) {
		/* Elapsed time using current modulation mode */
		if (lq_sta->flush_timer)
			flush_interval_passed =
				time_after(jiffies,
					   (unsigned long)(lq_sta->flush_timer +
							   (IWL_MVM_RS_STAY_IN_COLUMN_TIMEOUT * HZ)));

		/*
		 * Check if we should allow search for new modulation mode.
		 * If many frames have failed or succeeded, or we've used
		 * this same modulation for a long time, allow search, and
		 * reset history stats that keep track of whether we should
		 * allow a new search.  Also (below) reset all bitmaps and
		 * stats in active history.
		 */
		if (force_search ||
		    (lq_sta->total_failed > lq_sta->max_failure_limit) ||
		    (lq_sta->total_success > lq_sta->max_success_limit) ||
		    ((!lq_sta->search_better_tbl) &&
		     (lq_sta->flush_timer) && (flush_interval_passed))) {
			IWL_DEBUG_RATE(mvm,
				       "LQ: stay is expired %d %d %d\n",
				     lq_sta->total_failed,
				     lq_sta->total_success,
				     flush_interval_passed);

			/* Allow search for new mode */
			lq_sta->rs_state = RS_STATE_SEARCH_CYCLE_STARTED;
			IWL_DEBUG_RATE(mvm,
				       "Moving to RS_STATE_SEARCH_CYCLE_STARTED\n");
			lq_sta->total_failed = 0;
			lq_sta->total_success = 0;
			lq_sta->flush_timer = 0;
			/* mark the current column as visited */
			lq_sta->visited_columns = BIT(tbl->column);
		/*
		 * Else if we've used this modulation mode enough repetitions
		 * (regardless of elapsed time or success/failure), reset
		 * history bitmaps and rate-specific stats for all rates in
		 * active table.
		 */
		} else {
			lq_sta->table_count++;
			if (lq_sta->table_count >=
			    lq_sta->table_count_limit) {
				lq_sta->table_count = 0;

				IWL_DEBUG_RATE(mvm,
					       "LQ: stay in table clear win\n");
				rs_rate_scale_clear_tbl_windows(mvm, tbl);
			}
		}

		/* If transitioning to allow "search", reset all history
		 * bitmaps and stats in active table (this will become the new
		 * "search" table). */
		if (lq_sta->rs_state == RS_STATE_SEARCH_CYCLE_STARTED) {
			rs_rate_scale_clear_tbl_windows(mvm, tbl);
		}
	}
}