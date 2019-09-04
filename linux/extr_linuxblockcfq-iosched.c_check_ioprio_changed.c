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
struct cfq_queue {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ioc; } ;
struct cfq_io_cq {int ioprio; TYPE_2__ icq; } ;
struct cfq_data {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_3__ {int ioprio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 struct cfq_queue* cfq_get_queue (struct cfq_data*,int /*<<< orphan*/ ,struct cfq_io_cq*,struct bio*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_prio_changed (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int /*<<< orphan*/  cic_set_cfqq (struct cfq_io_cq*,struct cfq_queue*,int) ; 
 struct cfq_data* cic_to_cfqd (struct cfq_io_cq*) ; 
 struct cfq_queue* cic_to_cfqq (struct cfq_io_cq*,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void check_ioprio_changed(struct cfq_io_cq *cic, struct bio *bio)
{
	int ioprio = cic->icq.ioc->ioprio;
	struct cfq_data *cfqd = cic_to_cfqd(cic);
	struct cfq_queue *cfqq;

	/*
	 * Check whether ioprio has changed.  The condition may trigger
	 * spuriously on a newly created cic but there's no harm.
	 */
	if (unlikely(!cfqd) || likely(cic->ioprio == ioprio))
		return;

	cfqq = cic_to_cfqq(cic, false);
	if (cfqq) {
		cfq_put_queue(cfqq);
		cfqq = cfq_get_queue(cfqd, BLK_RW_ASYNC, cic, bio);
		cic_set_cfqq(cic, cfqq, false);
	}

	cfqq = cic_to_cfqq(cic, true);
	if (cfqq)
		cfq_mark_cfqq_prio_changed(cfqq);

	cic->ioprio = ioprio;
}