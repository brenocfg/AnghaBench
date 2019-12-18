#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nr_levels; } ;
struct smq_policy {TYPE_1__ dirty; int /*<<< orphan*/  bg_work; } ;
struct policy_work {int /*<<< orphan*/  cblock; int /*<<< orphan*/  oblock; int /*<<< orphan*/  op; } ;
struct entry {int /*<<< orphan*/  oblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLICY_WRITEBACK ; 
 int btracker_queue (int /*<<< orphan*/ ,struct policy_work*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_pending (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  infer_cblock (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  mark_pending (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  q_del (TYPE_1__*,struct entry*) ; 
 struct entry* q_peek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  q_push_front (TYPE_1__*,struct entry*) ; 

__attribute__((used)) static void queue_writeback(struct smq_policy *mq, bool idle)
{
	int r;
	struct policy_work work;
	struct entry *e;

	e = q_peek(&mq->dirty, mq->dirty.nr_levels, idle);
	if (e) {
		mark_pending(mq, e);
		q_del(&mq->dirty, e);

		work.op = POLICY_WRITEBACK;
		work.oblock = e->oblock;
		work.cblock = infer_cblock(mq, e);

		r = btracker_queue(mq->bg_work, &work, NULL);
		if (r) {
			clear_pending(mq, e);
			q_push_front(&mq->dirty, e);
		}
	}
}