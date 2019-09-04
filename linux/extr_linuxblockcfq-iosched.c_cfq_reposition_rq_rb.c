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
struct request {int /*<<< orphan*/  cmd_flags; } ;
struct cfq_queue {TYPE_1__* cfqd; int /*<<< orphan*/ * queued; int /*<<< orphan*/  sort_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  serving_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_CFQG (struct request*) ; 
 int /*<<< orphan*/  cfq_add_rq_rb (struct request*) ; 
 int /*<<< orphan*/  cfqg_stats_update_io_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfqg_stats_update_io_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elv_rb_del (int /*<<< orphan*/ *,struct request*) ; 
 size_t rq_is_sync (struct request*) ; 

__attribute__((used)) static void cfq_reposition_rq_rb(struct cfq_queue *cfqq, struct request *rq)
{
	elv_rb_del(&cfqq->sort_list, rq);
	cfqq->queued[rq_is_sync(rq)]--;
	cfqg_stats_update_io_remove(RQ_CFQG(rq), rq->cmd_flags);
	cfq_add_rq_rb(rq);
	cfqg_stats_update_io_add(RQ_CFQG(rq), cfqq->cfqd->serving_group,
				 rq->cmd_flags);
}