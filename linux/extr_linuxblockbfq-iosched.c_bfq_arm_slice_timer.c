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
typedef  int /*<<< orphan*/  u32 ;
struct bfq_queue {int wr_coeff; } ;
struct bfq_data {int /*<<< orphan*/  idle_slice_timer; int /*<<< orphan*/  last_idling_start; int /*<<< orphan*/  bfq_slice_idle; struct bfq_queue* in_service_queue; } ;

/* Variables and functions */
 scalar_t__ BFQQ_SEEKY (struct bfq_queue*) ; 
 int /*<<< orphan*/  BFQ_MIN_TT ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  bfq_mark_bfqq_wait_request (struct bfq_queue*) ; 
 scalar_t__ bfq_symmetric_scenario (struct bfq_data*) ; 
 int /*<<< orphan*/  bfqg_stats_set_start_idle_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfqq_group (struct bfq_queue*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static void bfq_arm_slice_timer(struct bfq_data *bfqd)
{
	struct bfq_queue *bfqq = bfqd->in_service_queue;
	u32 sl;

	bfq_mark_bfqq_wait_request(bfqq);

	/*
	 * We don't want to idle for seeks, but we do want to allow
	 * fair distribution of slice time for a process doing back-to-back
	 * seeks. So allow a little bit of time for him to submit a new rq.
	 */
	sl = bfqd->bfq_slice_idle;
	/*
	 * Unless the queue is being weight-raised or the scenario is
	 * asymmetric, grant only minimum idle time if the queue
	 * is seeky. A long idling is preserved for a weight-raised
	 * queue, or, more in general, in an asymmetric scenario,
	 * because a long idling is needed for guaranteeing to a queue
	 * its reserved share of the throughput (in particular, it is
	 * needed if the queue has a higher weight than some other
	 * queue).
	 */
	if (BFQQ_SEEKY(bfqq) && bfqq->wr_coeff == 1 &&
	    bfq_symmetric_scenario(bfqd))
		sl = min_t(u64, sl, BFQ_MIN_TT);

	bfqd->last_idling_start = ktime_get();
	hrtimer_start(&bfqd->idle_slice_timer, ns_to_ktime(sl),
		      HRTIMER_MODE_REL);
	bfqg_stats_set_start_idle_time(bfqq_group(bfqq));
}