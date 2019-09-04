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
struct request {int cmd_flags; } ;
struct cfq_queue {scalar_t__ ioprio_class; int /*<<< orphan*/  sort_list; int /*<<< orphan*/  prio_pending; int /*<<< orphan*/  cfqg; } ;
struct cfq_data {scalar_t__ serving_wl_type; int /*<<< orphan*/  active_cic; struct cfq_queue* active_queue; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int REQ_PRIO ; 
 scalar_t__ SYNC_NOIDLE_WORKLOAD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cfq_cfqq_must_dispatch (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_cfqq_sync (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_cfqq_wait_request (struct cfq_queue*) ; 
 scalar_t__ cfq_class_idle (struct cfq_queue*) ; 
 scalar_t__ cfq_class_rt (struct cfq_queue*) ; 
 scalar_t__ cfq_rq_close (struct cfq_data*,struct cfq_queue*,struct request*) ; 
 int /*<<< orphan*/  cfq_should_idle (struct cfq_data*,struct cfq_queue*) ; 
 scalar_t__ cfq_slice_used (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfqg_is_descendant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cfqq_type (struct cfq_queue*) ; 
 scalar_t__ rq_is_sync (struct request*) ; 

__attribute__((used)) static bool
cfq_should_preempt(struct cfq_data *cfqd, struct cfq_queue *new_cfqq,
		   struct request *rq)
{
	struct cfq_queue *cfqq;

	cfqq = cfqd->active_queue;
	if (!cfqq)
		return false;

	if (cfq_class_idle(new_cfqq))
		return false;

	if (cfq_class_idle(cfqq))
		return true;

	/*
	 * Don't allow a non-RT request to preempt an ongoing RT cfqq timeslice.
	 */
	if (cfq_class_rt(cfqq) && !cfq_class_rt(new_cfqq))
		return false;

	/*
	 * if the new request is sync, but the currently running queue is
	 * not, let the sync request have priority.
	 */
	if (rq_is_sync(rq) && !cfq_cfqq_sync(cfqq) && !cfq_cfqq_must_dispatch(cfqq))
		return true;

	/*
	 * Treat ancestors of current cgroup the same way as current cgroup.
	 * For anybody else we disallow preemption to guarantee service
	 * fairness among cgroups.
	 */
	if (!cfqg_is_descendant(cfqq->cfqg, new_cfqq->cfqg))
		return false;

	if (cfq_slice_used(cfqq))
		return true;

	/*
	 * Allow an RT request to pre-empt an ongoing non-RT cfqq timeslice.
	 */
	if (cfq_class_rt(new_cfqq) && !cfq_class_rt(cfqq))
		return true;

	WARN_ON_ONCE(cfqq->ioprio_class != new_cfqq->ioprio_class);
	/* Allow preemption only if we are idling on sync-noidle tree */
	if (cfqd->serving_wl_type == SYNC_NOIDLE_WORKLOAD &&
	    cfqq_type(new_cfqq) == SYNC_NOIDLE_WORKLOAD &&
	    RB_EMPTY_ROOT(&cfqq->sort_list))
		return true;

	/*
	 * So both queues are sync. Let the new request get disk time if
	 * it's a metadata request and the current queue is doing regular IO.
	 */
	if ((rq->cmd_flags & REQ_PRIO) && !cfqq->prio_pending)
		return true;

	/* An idle queue should not be idle now for some reason */
	if (RB_EMPTY_ROOT(&cfqq->sort_list) && !cfq_should_idle(cfqd, cfqq))
		return true;

	if (!cfqd->active_cic || !cfq_cfqq_wait_request(cfqq))
		return false;

	/*
	 * if this request is as-good as one we would expect from the
	 * current cfqq, let it preempt
	 */
	if (cfq_rq_close(cfqd, cfqq, rq))
		return true;

	return false;
}