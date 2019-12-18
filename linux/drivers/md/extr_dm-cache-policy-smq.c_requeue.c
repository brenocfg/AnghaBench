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
struct smq_policy {int current_writeback_sentinels; int /*<<< orphan*/  writeback_sentinel_alloc; int /*<<< orphan*/  dirty; int /*<<< orphan*/  clean; int /*<<< orphan*/  cache_hit_bits; } ;
struct entry {int /*<<< orphan*/  level; int /*<<< orphan*/  dirty; scalar_t__ pending_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_sentinel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  infer_cblock (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  q_requeue (int /*<<< orphan*/ *,struct entry*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void requeue(struct smq_policy *mq, struct entry *e)
{
	/*
	 * Pending work has temporarily been taken out of the queues.
	 */
	if (e->pending_work)
		return;

	if (!test_and_set_bit(from_cblock(infer_cblock(mq, e)), mq->cache_hit_bits)) {
		if (!e->dirty) {
			q_requeue(&mq->clean, e, 1u, NULL, NULL);
			return;
		}

		q_requeue(&mq->dirty, e, 1u,
			  get_sentinel(&mq->writeback_sentinel_alloc, e->level, !mq->current_writeback_sentinels),
			  get_sentinel(&mq->writeback_sentinel_alloc, e->level, mq->current_writeback_sentinels));
	}
}