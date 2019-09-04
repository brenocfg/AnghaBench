#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ttime_mean; int /*<<< orphan*/  ttime_samples; } ;
struct bfq_queue {TYPE_3__ ttime; scalar_t__ split_time; } ;
struct TYPE_5__ {TYPE_1__* ioc; } ;
struct bfq_io_cq {TYPE_2__ icq; } ;
struct bfq_data {scalar_t__ bfq_slice_idle; scalar_t__ bfq_wr_min_idle_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  active_ref; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfq_bfqq_sync (struct bfq_queue*) ; 
 scalar_t__ bfq_class_idle (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,int) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_has_short_ttime (struct bfq_queue*) ; 
 scalar_t__ bfq_sample_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_after_eq_jiffies (scalar_t__) ; 

__attribute__((used)) static void bfq_update_has_short_ttime(struct bfq_data *bfqd,
				       struct bfq_queue *bfqq,
				       struct bfq_io_cq *bic)
{
	bool has_short_ttime = true;

	/*
	 * No need to update has_short_ttime if bfqq is async or in
	 * idle io prio class, or if bfq_slice_idle is zero, because
	 * no device idling is performed for bfqq in this case.
	 */
	if (!bfq_bfqq_sync(bfqq) || bfq_class_idle(bfqq) ||
	    bfqd->bfq_slice_idle == 0)
		return;

	/* Idle window just restored, statistics are meaningless. */
	if (time_is_after_eq_jiffies(bfqq->split_time +
				     bfqd->bfq_wr_min_idle_time))
		return;

	/* Think time is infinite if no process is linked to
	 * bfqq. Otherwise check average think time to
	 * decide whether to mark as has_short_ttime
	 */
	if (atomic_read(&bic->icq.ioc->active_ref) == 0 ||
	    (bfq_sample_valid(bfqq->ttime.ttime_samples) &&
	     bfqq->ttime.ttime_mean > bfqd->bfq_slice_idle))
		has_short_ttime = false;

	bfq_log_bfqq(bfqd, bfqq, "update_has_short_ttime: has_short_ttime %d",
		     has_short_ttime);

	if (has_short_ttime)
		bfq_mark_bfqq_has_short_ttime(bfqq);
	else
		bfq_clear_bfqq_has_short_ttime(bfqq);
}