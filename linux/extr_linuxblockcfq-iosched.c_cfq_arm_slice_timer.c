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
typedef  scalar_t__ u64 ;
struct cfq_rb_root {int /*<<< orphan*/  ttime; } ;
struct cfq_queue {scalar_t__ slice_end; TYPE_4__* cfqg; scalar_t__ dispatched; int /*<<< orphan*/  sort_list; struct cfq_rb_root* service_tree; } ;
struct TYPE_7__ {scalar_t__ ttime_mean; int /*<<< orphan*/  ttime_samples; } ;
struct TYPE_6__ {TYPE_1__* ioc; } ;
struct cfq_io_cq {TYPE_3__ ttime; TYPE_2__ icq; } ;
struct cfq_data {scalar_t__ cfq_group_idle; scalar_t__ cfq_slice_idle; int /*<<< orphan*/  idle_slice_timer; struct cfq_io_cq* active_cic; scalar_t__ hw_tag; int /*<<< orphan*/  queue; struct cfq_queue* active_queue; } ;
struct TYPE_8__ {int nr_cfqq; } ;
struct TYPE_5__ {int /*<<< orphan*/  active_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_queue_nonrot (int /*<<< orphan*/ ) ; 
 int cfq_cfqq_slice_new (struct cfq_queue*) ; 
 scalar_t__ cfq_io_thinktime_big (struct cfq_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_wait_request (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_should_idle (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfqg_stats_set_start_idle_time (TYPE_4__*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  ns_to_ktime (scalar_t__) ; 
 scalar_t__ sample_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfq_arm_slice_timer(struct cfq_data *cfqd)
{
	struct cfq_queue *cfqq = cfqd->active_queue;
	struct cfq_rb_root *st = cfqq->service_tree;
	struct cfq_io_cq *cic;
	u64 sl, group_idle = 0;
	u64 now = ktime_get_ns();

	/*
	 * SSD device without seek penalty, disable idling. But only do so
	 * for devices that support queuing, otherwise we still have a problem
	 * with sync vs async workloads.
	 */
	if (blk_queue_nonrot(cfqd->queue) && cfqd->hw_tag &&
		!cfqd->cfq_group_idle)
		return;

	WARN_ON(!RB_EMPTY_ROOT(&cfqq->sort_list));
	WARN_ON(cfq_cfqq_slice_new(cfqq));

	/*
	 * idle is disabled, either manually or by past process history
	 */
	if (!cfq_should_idle(cfqd, cfqq)) {
		/* no queue idling. Check for group idling */
		if (cfqd->cfq_group_idle)
			group_idle = cfqd->cfq_group_idle;
		else
			return;
	}

	/*
	 * still active requests from this queue, don't idle
	 */
	if (cfqq->dispatched)
		return;

	/*
	 * task has exited, don't wait
	 */
	cic = cfqd->active_cic;
	if (!cic || !atomic_read(&cic->icq.ioc->active_ref))
		return;

	/*
	 * If our average think time is larger than the remaining time
	 * slice, then don't idle. This avoids overrunning the allotted
	 * time slice.
	 */
	if (sample_valid(cic->ttime.ttime_samples) &&
	    (cfqq->slice_end - now < cic->ttime.ttime_mean)) {
		cfq_log_cfqq(cfqd, cfqq, "Not idling. think_time:%llu",
			     cic->ttime.ttime_mean);
		return;
	}

	/*
	 * There are other queues in the group or this is the only group and
	 * it has too big thinktime, don't do group idle.
	 */
	if (group_idle &&
	    (cfqq->cfqg->nr_cfqq > 1 ||
	     cfq_io_thinktime_big(cfqd, &st->ttime, true)))
		return;

	cfq_mark_cfqq_wait_request(cfqq);

	if (group_idle)
		sl = cfqd->cfq_group_idle;
	else
		sl = cfqd->cfq_slice_idle;

	hrtimer_start(&cfqd->idle_slice_timer, ns_to_ktime(sl),
		      HRTIMER_MODE_REL);
	cfqg_stats_set_start_idle_time(cfqq->cfqg);
	cfq_log_cfqq(cfqd, cfqq, "arm_idle: %llu group_idle: %d", sl,
			group_idle ? 1 : 0);
}