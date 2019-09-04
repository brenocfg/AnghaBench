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
struct request_queue {int dummy; } ;
struct request {scalar_t__ start_time_ns; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  io_start_time_ns; } ;
struct TYPE_6__ {scalar_t__ last_end_request; } ;
struct cfq_rb_root {TYPE_2__ ttime; } ;
struct cfq_queue {scalar_t__ slice_end; int /*<<< orphan*/  sort_list; int /*<<< orphan*/  cfqg; struct cfq_rb_root* service_tree; int /*<<< orphan*/  dispatched; struct cfq_data* cfqd; } ;
struct cfq_data {scalar_t__* cfq_fifo_expire; scalar_t__ cfq_slice_idle; scalar_t__ cfq_group_idle; int /*<<< orphan*/  rq_in_driver; struct cfq_queue* active_queue; scalar_t__ last_delayed_sync; int /*<<< orphan*/ * rq_in_flight; } ;
struct TYPE_8__ {int /*<<< orphan*/  dispatched; } ;
struct TYPE_5__ {scalar_t__ last_end_request; } ;
struct TYPE_7__ {TYPE_1__ ttime; } ;

/* Variables and functions */
 int RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 TYPE_4__* RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 TYPE_3__* RQ_CIC (struct request*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfq_arm_slice_timer (struct cfq_data*) ; 
 scalar_t__ cfq_cfqq_on_rr (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_slice_new (struct cfq_queue*) ; 
 size_t cfq_cfqq_sync (struct cfq_queue*) ; 
 scalar_t__ cfq_class_idle (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_slice_new (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_close_cooperator (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,...) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_wait_busy (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_schedule_dispatch (struct cfq_data*) ; 
 int /*<<< orphan*/  cfq_set_prio_slice (struct cfq_data*,struct cfq_queue*) ; 
 scalar_t__ cfq_should_wait_busy (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_slice_expired (struct cfq_data*,int) ; 
 scalar_t__ cfq_slice_used (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_update_hw_tag (struct cfq_data*) ; 
 int /*<<< orphan*/  cfqg_stats_update_completion (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfqq_class (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfqq_type (struct cfq_queue*) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  req_noidle (struct request*) ; 
 int rq_is_sync (struct request*) ; 
 struct cfq_rb_root* st_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfq_completed_request(struct request_queue *q, struct request *rq)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);
	struct cfq_data *cfqd = cfqq->cfqd;
	const int sync = rq_is_sync(rq);
	u64 now = ktime_get_ns();

	cfq_log_cfqq(cfqd, cfqq, "complete rqnoidle %d", req_noidle(rq));

	cfq_update_hw_tag(cfqd);

	WARN_ON(!cfqd->rq_in_driver);
	WARN_ON(!cfqq->dispatched);
	cfqd->rq_in_driver--;
	cfqq->dispatched--;
	(RQ_CFQG(rq))->dispatched--;
	cfqg_stats_update_completion(cfqq->cfqg, rq->start_time_ns,
				     rq->io_start_time_ns, rq->cmd_flags);

	cfqd->rq_in_flight[cfq_cfqq_sync(cfqq)]--;

	if (sync) {
		struct cfq_rb_root *st;

		RQ_CIC(rq)->ttime.last_end_request = now;

		if (cfq_cfqq_on_rr(cfqq))
			st = cfqq->service_tree;
		else
			st = st_for(cfqq->cfqg, cfqq_class(cfqq),
					cfqq_type(cfqq));

		st->ttime.last_end_request = now;
		if (rq->start_time_ns + cfqd->cfq_fifo_expire[1] <= now)
			cfqd->last_delayed_sync = now;
	}

#ifdef CONFIG_CFQ_GROUP_IOSCHED
	cfqq->cfqg->ttime.last_end_request = now;
#endif

	/*
	 * If this is the active queue, check if it needs to be expired,
	 * or if we want to idle in case it has no pending requests.
	 */
	if (cfqd->active_queue == cfqq) {
		const bool cfqq_empty = RB_EMPTY_ROOT(&cfqq->sort_list);

		if (cfq_cfqq_slice_new(cfqq)) {
			cfq_set_prio_slice(cfqd, cfqq);
			cfq_clear_cfqq_slice_new(cfqq);
		}

		/*
		 * Should we wait for next request to come in before we expire
		 * the queue.
		 */
		if (cfq_should_wait_busy(cfqd, cfqq)) {
			u64 extend_sl = cfqd->cfq_slice_idle;
			if (!cfqd->cfq_slice_idle)
				extend_sl = cfqd->cfq_group_idle;
			cfqq->slice_end = now + extend_sl;
			cfq_mark_cfqq_wait_busy(cfqq);
			cfq_log_cfqq(cfqd, cfqq, "will busy wait");
		}

		/*
		 * Idling is not enabled on:
		 * - expired queues
		 * - idle-priority queues
		 * - async queues
		 * - queues with still some requests queued
		 * - when there is a close cooperator
		 */
		if (cfq_slice_used(cfqq) || cfq_class_idle(cfqq))
			cfq_slice_expired(cfqd, 1);
		else if (sync && cfqq_empty &&
			 !cfq_close_cooperator(cfqd, cfqq)) {
			cfq_arm_slice_timer(cfqd);
		}
	}

	if (!cfqd->rq_in_driver)
		cfq_schedule_dispatch(cfqd);
}