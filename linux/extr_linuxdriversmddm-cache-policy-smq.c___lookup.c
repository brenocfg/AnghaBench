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
struct smq_policy {int /*<<< orphan*/  cache_stats; int /*<<< orphan*/  table; } ;
struct policy_work {int dummy; } ;
struct entry {int /*<<< orphan*/  level; } ;
typedef  enum promote_result { ____Placeholder_promote_result } promote_result ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int ENOENT ; 
 int PROMOTE_NOT ; 
 struct entry* h_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infer_cblock (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  queue_promotion (struct smq_policy*,int /*<<< orphan*/ ,struct policy_work**) ; 
 int /*<<< orphan*/  requeue (struct smq_policy*,struct entry*) ; 
 int should_promote (struct smq_policy*,struct entry*,int,int) ; 
 int /*<<< orphan*/  stats_level_accessed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_miss (int /*<<< orphan*/ *) ; 
 struct entry* update_hotspot_queue (struct smq_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __lookup(struct smq_policy *mq, dm_oblock_t oblock, dm_cblock_t *cblock,
		    int data_dir, bool fast_copy,
		    struct policy_work **work, bool *background_work)
{
	struct entry *e, *hs_e;
	enum promote_result pr;

	*background_work = false;

	e = h_lookup(&mq->table, oblock);
	if (e) {
		stats_level_accessed(&mq->cache_stats, e->level);

		requeue(mq, e);
		*cblock = infer_cblock(mq, e);
		return 0;

	} else {
		stats_miss(&mq->cache_stats);

		/*
		 * The hotspot queue only gets updated with misses.
		 */
		hs_e = update_hotspot_queue(mq, oblock);

		pr = should_promote(mq, hs_e, data_dir, fast_copy);
		if (pr != PROMOTE_NOT) {
			queue_promotion(mq, oblock, work);
			*background_work = true;
		}

		return -ENOENT;
	}
}