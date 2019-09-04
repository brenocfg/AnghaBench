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
struct TYPE_2__ {int prio_changed; } ;
struct bfq_queue {unsigned int wr_coeff; scalar_t__ last_wr_start_finish; scalar_t__ wr_cur_max_time; TYPE_1__ entity; int /*<<< orphan*/  bfqd; scalar_t__ wr_start_at_switch_to_srt; int /*<<< orphan*/  ttime; } ;
struct bfq_io_cq {unsigned int saved_wr_coeff; scalar_t__ saved_last_wr_start_finish; scalar_t__ saved_wr_cur_max_time; scalar_t__ saved_wr_start_at_switch_to_srt; int /*<<< orphan*/  saved_ttime; scalar_t__ saved_IO_bound; scalar_t__ saved_has_short_ttime; } ;
struct bfq_data {scalar_t__ bfq_wr_rt_max_time; int /*<<< orphan*/  wr_busy_queues; } ;

/* Variables and functions */
 scalar_t__ bfq_bfqq_busy (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_in_large_burst (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_IO_bound (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (int /*<<< orphan*/ ,struct bfq_queue*,char*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_IO_bound (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_has_short_ttime (struct bfq_queue*) ; 
 scalar_t__ bfq_wr_duration (struct bfq_data*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  switch_back_to_interactive_wr (struct bfq_queue*,struct bfq_data*) ; 
 scalar_t__ time_is_after_eq_jiffies (scalar_t__) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void
bfq_bfqq_resume_state(struct bfq_queue *bfqq, struct bfq_data *bfqd,
		      struct bfq_io_cq *bic, bool bfq_already_existing)
{
	unsigned int old_wr_coeff = bfqq->wr_coeff;
	bool busy = bfq_already_existing && bfq_bfqq_busy(bfqq);

	if (bic->saved_has_short_ttime)
		bfq_mark_bfqq_has_short_ttime(bfqq);
	else
		bfq_clear_bfqq_has_short_ttime(bfqq);

	if (bic->saved_IO_bound)
		bfq_mark_bfqq_IO_bound(bfqq);
	else
		bfq_clear_bfqq_IO_bound(bfqq);

	bfqq->ttime = bic->saved_ttime;
	bfqq->wr_coeff = bic->saved_wr_coeff;
	bfqq->wr_start_at_switch_to_srt = bic->saved_wr_start_at_switch_to_srt;
	bfqq->last_wr_start_finish = bic->saved_last_wr_start_finish;
	bfqq->wr_cur_max_time = bic->saved_wr_cur_max_time;

	if (bfqq->wr_coeff > 1 && (bfq_bfqq_in_large_burst(bfqq) ||
	    time_is_before_jiffies(bfqq->last_wr_start_finish +
				   bfqq->wr_cur_max_time))) {
		if (bfqq->wr_cur_max_time == bfqd->bfq_wr_rt_max_time &&
		    !bfq_bfqq_in_large_burst(bfqq) &&
		    time_is_after_eq_jiffies(bfqq->wr_start_at_switch_to_srt +
					     bfq_wr_duration(bfqd))) {
			switch_back_to_interactive_wr(bfqq, bfqd);
		} else {
			bfqq->wr_coeff = 1;
			bfq_log_bfqq(bfqq->bfqd, bfqq,
				     "resume state: switching off wr");
		}
	}

	/* make sure weight will be updated, however we got here */
	bfqq->entity.prio_changed = 1;

	if (likely(!busy))
		return;

	if (old_wr_coeff == 1 && bfqq->wr_coeff > 1)
		bfqd->wr_busy_queues++;
	else if (old_wr_coeff > 1 && bfqq->wr_coeff == 1)
		bfqd->wr_busy_queues--;
}