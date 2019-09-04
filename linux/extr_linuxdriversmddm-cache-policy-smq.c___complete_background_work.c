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
struct smq_policy {int /*<<< orphan*/  bg_work; int /*<<< orphan*/  cache_alloc; int /*<<< orphan*/  table; } ;
struct policy_work {int op; int /*<<< orphan*/  oblock; int /*<<< orphan*/  cblock; } ;
struct entry {int /*<<< orphan*/  level; int /*<<< orphan*/  oblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_CACHE_LEVELS ; 
#define  POLICY_DEMOTE 130 
#define  POLICY_PROMOTE 129 
#define  POLICY_WRITEBACK 128 
 int /*<<< orphan*/  btracker_complete (int /*<<< orphan*/ ,struct policy_work*) ; 
 int /*<<< orphan*/  clear_pending (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  free_entry (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 struct entry* get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_remove (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  push (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  push_queue (struct smq_policy*,struct entry*) ; 

__attribute__((used)) static void __complete_background_work(struct smq_policy *mq,
				       struct policy_work *work,
				       bool success)
{
	struct entry *e = get_entry(&mq->cache_alloc,
				    from_cblock(work->cblock));

	switch (work->op) {
	case POLICY_PROMOTE:
		// !h, !q, a
		clear_pending(mq, e);
		if (success) {
			e->oblock = work->oblock;
			e->level = NR_CACHE_LEVELS - 1;
			push(mq, e);
			// h, q, a
		} else {
			free_entry(&mq->cache_alloc, e);
			// !h, !q, !a
		}
		break;

	case POLICY_DEMOTE:
		// h, !q, a
		if (success) {
			h_remove(&mq->table, e);
			free_entry(&mq->cache_alloc, e);
			// !h, !q, !a
		} else {
			clear_pending(mq, e);
			push_queue(mq, e);
			// h, q, a
		}
		break;

	case POLICY_WRITEBACK:
		// h, !q, a
		clear_pending(mq, e);
		push_queue(mq, e);
		// h, q, a
		break;
	}

	btracker_complete(mq->bg_work, work);
}