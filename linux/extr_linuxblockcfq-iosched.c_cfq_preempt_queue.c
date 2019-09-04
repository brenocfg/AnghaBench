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
struct cfq_queue {scalar_t__ slice_end; TYPE_1__* cfqg; } ;
struct cfq_data {struct cfq_queue* active_queue; } ;
typedef  enum wl_type_t { ____Placeholder_wl_type_t } wl_type_t ;
struct TYPE_2__ {scalar_t__ saved_wl_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cfq_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_slice_new (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_service_tree_add (struct cfq_data*,struct cfq_queue*,int) ; 
 int /*<<< orphan*/  cfq_slice_expired (struct cfq_data*,int) ; 
 int cfqq_type (struct cfq_queue*) ; 

__attribute__((used)) static void cfq_preempt_queue(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	enum wl_type_t old_type = cfqq_type(cfqd->active_queue);

	cfq_log_cfqq(cfqd, cfqq, "preempt");
	cfq_slice_expired(cfqd, 1);

	/*
	 * workload type is changed, don't save slice, otherwise preempt
	 * doesn't happen
	 */
	if (old_type != cfqq_type(cfqq))
		cfqq->cfqg->saved_wl_slice = 0;

	/*
	 * Put the new queue at the front of the of the current list,
	 * so we know that it will be selected next.
	 */
	BUG_ON(!cfq_cfqq_on_rr(cfqq));

	cfq_service_tree_add(cfqd, cfqq, 1);

	cfqq->slice_end = 0;
	cfq_mark_cfqq_slice_new(cfqq);
}