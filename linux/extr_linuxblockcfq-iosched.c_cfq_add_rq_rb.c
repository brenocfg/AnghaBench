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
struct request {int dummy; } ;
struct cfq_queue {struct request* next_rq; int /*<<< orphan*/  sort_list; int /*<<< orphan*/ * queued; struct cfq_data* cfqd; } ;
struct cfq_data {int /*<<< orphan*/  last_position; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 int /*<<< orphan*/  cfq_add_cfqq_rr (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_cfqq_on_rr (struct cfq_queue*) ; 
 struct request* cfq_choose_req (struct cfq_data*,struct request*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_prio_tree_add (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  elv_rb_add (int /*<<< orphan*/ *,struct request*) ; 
 size_t rq_is_sync (struct request*) ; 

__attribute__((used)) static void cfq_add_rq_rb(struct request *rq)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);
	struct cfq_data *cfqd = cfqq->cfqd;
	struct request *prev;

	cfqq->queued[rq_is_sync(rq)]++;

	elv_rb_add(&cfqq->sort_list, rq);

	if (!cfq_cfqq_on_rr(cfqq))
		cfq_add_cfqq_rr(cfqd, cfqq);

	/*
	 * check if this request is a better next-serve candidate
	 */
	prev = cfqq->next_rq;
	cfqq->next_rq = cfq_choose_req(cfqd, cfqq->next_rq, rq, cfqd->last_position);

	/*
	 * adjust priority tree position, if ->next_rq changes
	 */
	if (prev != cfqq->next_rq)
		cfq_prio_tree_add(cfqd, cfqq);

	BUG_ON(!cfqq->next_rq);
}