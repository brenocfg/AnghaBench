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
struct TYPE_4__ {int nr_levels; } ;
struct smq_policy {TYPE_1__ clean; int /*<<< orphan*/  bg_work; int /*<<< orphan*/  migrations_allowed; } ;
struct policy_work {int /*<<< orphan*/  cblock; int /*<<< orphan*/  oblock; int /*<<< orphan*/  op; } ;
struct entry {int /*<<< orphan*/  oblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLICY_DEMOTE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int btracker_queue (int /*<<< orphan*/ ,struct policy_work*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_target_met (struct smq_policy*,int) ; 
 int /*<<< orphan*/  clear_pending (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  infer_cblock (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  mark_pending (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  q_del (TYPE_1__*,struct entry*) ; 
 struct entry* q_peek (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  q_push_front (TYPE_1__*,struct entry*) ; 
 int /*<<< orphan*/  queue_writeback (struct smq_policy*,int) ; 

__attribute__((used)) static void queue_demotion(struct smq_policy *mq)
{
	int r;
	struct policy_work work;
	struct entry *e;

	if (WARN_ON_ONCE(!mq->migrations_allowed))
		return;

	e = q_peek(&mq->clean, mq->clean.nr_levels / 2, true);
	if (!e) {
		if (!clean_target_met(mq, true))
			queue_writeback(mq, false);
		return;
	}

	mark_pending(mq, e);
	q_del(&mq->clean, e);

	work.op = POLICY_DEMOTE;
	work.oblock = e->oblock;
	work.cblock = infer_cblock(mq, e);
	r = btracker_queue(mq->bg_work, &work, NULL);
	if (r) {
		clear_pending(mq, e);
		q_push_front(&mq->clean, e);
	}
}