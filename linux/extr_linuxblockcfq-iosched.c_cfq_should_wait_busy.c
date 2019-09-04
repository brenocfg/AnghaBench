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
typedef  scalar_t__ u64 ;
struct cfq_queue {scalar_t__ slice_end; TYPE_2__* cfqg; int /*<<< orphan*/  sort_list; } ;
struct TYPE_3__ {scalar_t__ ttime_mean; int /*<<< orphan*/  ttime_samples; } ;
struct cfq_io_cq {TYPE_1__ ttime; } ;
struct cfq_data {struct cfq_io_cq* active_cic; } ;
struct TYPE_4__ {int nr_cfqq; int /*<<< orphan*/  ttime; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 scalar_t__ cfq_io_thinktime_big (struct cfq_data*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cfq_slice_used (struct cfq_queue*) ; 
 scalar_t__ jiffies_to_nsecs (int) ; 
 scalar_t__ ktime_get_ns () ; 
 scalar_t__ sample_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cfq_should_wait_busy(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	struct cfq_io_cq *cic = cfqd->active_cic;
	u64 now = ktime_get_ns();

	/* If the queue already has requests, don't wait */
	if (!RB_EMPTY_ROOT(&cfqq->sort_list))
		return false;

	/* If there are other queues in the group, don't wait */
	if (cfqq->cfqg->nr_cfqq > 1)
		return false;

	/* the only queue in the group, but think time is big */
	if (cfq_io_thinktime_big(cfqd, &cfqq->cfqg->ttime, true))
		return false;

	if (cfq_slice_used(cfqq))
		return true;

	/* if slice left is less than think time, wait busy */
	if (cic && sample_valid(cic->ttime.ttime_samples)
	    && (cfqq->slice_end - now < cic->ttime.ttime_mean))
		return true;

	/*
	 * If think times is less than a jiffy than ttime_mean=0 and above
	 * will not be true. It might happen that slice has not expired yet
	 * but will expire soon (4-5 ns) during select_queue(). To cover the
	 * case where think time is less than a jiffy, mark the queue wait
	 * busy if only 1 jiffy is left in the slice.
	 */
	if (cfqq->slice_end - now <= jiffies_to_nsecs(1))
		return true;

	return false;
}