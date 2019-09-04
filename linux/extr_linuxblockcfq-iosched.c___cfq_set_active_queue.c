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
struct cfq_queue {scalar_t__ nr_sectors; scalar_t__ slice_dispatch; scalar_t__ slice_end; scalar_t__ allocated_slice; int /*<<< orphan*/  dispatch_start; scalar_t__ slice_start; int /*<<< orphan*/  cfqg; } ;
struct cfq_data {struct cfq_queue* active_queue; int /*<<< orphan*/  serving_wl_type; int /*<<< orphan*/  serving_wl_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_clear_cfqq_fifo_expire (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_must_alloc_slice (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_must_dispatch (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_wait_request (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_del_timer (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_slice_new (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfqg_stats_update_avg_queue_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 

__attribute__((used)) static void __cfq_set_active_queue(struct cfq_data *cfqd,
				   struct cfq_queue *cfqq)
{
	if (cfqq) {
		cfq_log_cfqq(cfqd, cfqq, "set_active wl_class:%d wl_type:%d",
				cfqd->serving_wl_class, cfqd->serving_wl_type);
		cfqg_stats_update_avg_queue_size(cfqq->cfqg);
		cfqq->slice_start = 0;
		cfqq->dispatch_start = ktime_get_ns();
		cfqq->allocated_slice = 0;
		cfqq->slice_end = 0;
		cfqq->slice_dispatch = 0;
		cfqq->nr_sectors = 0;

		cfq_clear_cfqq_wait_request(cfqq);
		cfq_clear_cfqq_must_dispatch(cfqq);
		cfq_clear_cfqq_must_alloc_slice(cfqq);
		cfq_clear_cfqq_fifo_expire(cfqq);
		cfq_mark_cfqq_slice_new(cfqq);

		cfq_del_timer(cfqd, cfqq);
	}

	cfqd->active_queue = cfqq;
}