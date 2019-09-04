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
struct smq_policy {int /*<<< orphan*/  cache_alloc; int /*<<< orphan*/  bg_work; int /*<<< orphan*/  migrations_allowed; } ;
struct policy_work {int /*<<< orphan*/  cblock; int /*<<< orphan*/  oblock; int /*<<< orphan*/  op; } ;
struct entry {int pending_work; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  POLICY_PROMOTE ; 
 struct entry* alloc_entry (int /*<<< orphan*/ *) ; 
 scalar_t__ allocator_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ btracker_promotion_already_present (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btracker_queue (int /*<<< orphan*/ ,struct policy_work*,struct policy_work**) ; 
 int /*<<< orphan*/  free_entry (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  free_target_met (struct smq_policy*) ; 
 int /*<<< orphan*/  infer_cblock (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  queue_demotion (struct smq_policy*) ; 

__attribute__((used)) static void queue_promotion(struct smq_policy *mq, dm_oblock_t oblock,
			    struct policy_work **workp)
{
	int r;
	struct entry *e;
	struct policy_work work;

	if (!mq->migrations_allowed)
		return;

	if (allocator_empty(&mq->cache_alloc)) {
		/*
		 * We always claim to be 'idle' to ensure some demotions happen
		 * with continuous loads.
		 */
		if (!free_target_met(mq))
			queue_demotion(mq);
		return;
	}

	if (btracker_promotion_already_present(mq->bg_work, oblock))
		return;

	/*
	 * We allocate the entry now to reserve the cblock.  If the
	 * background work is aborted we must remember to free it.
	 */
	e = alloc_entry(&mq->cache_alloc);
	BUG_ON(!e);
	e->pending_work = true;
	work.op = POLICY_PROMOTE;
	work.oblock = oblock;
	work.cblock = infer_cblock(mq, e);
	r = btracker_queue(mq->bg_work, &work, workp);
	if (r)
		free_entry(&mq->cache_alloc, e);
}