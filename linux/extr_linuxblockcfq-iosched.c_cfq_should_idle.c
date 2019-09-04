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
struct cfq_rb_root {int count; int /*<<< orphan*/  ttime; } ;
struct cfq_queue {struct cfq_rb_root* service_tree; } ;
struct cfq_data {scalar_t__ hw_tag; int /*<<< orphan*/  queue; int /*<<< orphan*/  cfq_slice_idle; } ;
typedef  enum wl_class_t { ____Placeholder_wl_class_t } wl_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IDLE_WORKLOAD ; 
 scalar_t__ blk_queue_nonrot (int /*<<< orphan*/ ) ; 
 scalar_t__ cfq_cfqq_idle_window (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_sync (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_io_thinktime_big (struct cfq_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,int) ; 
 int cfqq_class (struct cfq_queue*) ; 

__attribute__((used)) static bool cfq_should_idle(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	enum wl_class_t wl_class = cfqq_class(cfqq);
	struct cfq_rb_root *st = cfqq->service_tree;

	BUG_ON(!st);
	BUG_ON(!st->count);

	if (!cfqd->cfq_slice_idle)
		return false;

	/* We never do for idle class queues. */
	if (wl_class == IDLE_WORKLOAD)
		return false;

	/* We do for queues that were marked with idle window flag. */
	if (cfq_cfqq_idle_window(cfqq) &&
	   !(blk_queue_nonrot(cfqd->queue) && cfqd->hw_tag))
		return true;

	/*
	 * Otherwise, we do only if they are the last ones
	 * in their service tree.
	 */
	if (st->count == 1 && cfq_cfqq_sync(cfqq) &&
	   !cfq_io_thinktime_big(cfqd, &st->ttime, false))
		return true;
	cfq_log_cfqq(cfqd, cfqq, "Not idling. st->count:%d", st->count);
	return false;
}