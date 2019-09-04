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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct blkcg_gq {int dummy; } ;
struct blkcg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENODEV ; 
 struct blkcg_gq* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct blkcg_gq*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct blkcg_gq* __blkg_lookup (struct blkcg*,struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_bypass (struct request_queue*) ; 
 scalar_t__ blk_queue_dying (struct request_queue*) ; 
 struct blkcg* blkcg_parent (struct blkcg*) ; 
 struct blkcg_gq* blkg_create (struct blkcg*,struct request_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct blkcg_gq *blkg_lookup_create(struct blkcg *blkcg,
				    struct request_queue *q)
{
	struct blkcg_gq *blkg;

	WARN_ON_ONCE(!rcu_read_lock_held());
	lockdep_assert_held(q->queue_lock);

	/*
	 * This could be the first entry point of blkcg implementation and
	 * we shouldn't allow anything to go through for a bypassing queue.
	 */
	if (unlikely(blk_queue_bypass(q)))
		return ERR_PTR(blk_queue_dying(q) ? -ENODEV : -EBUSY);

	blkg = __blkg_lookup(blkcg, q, true);
	if (blkg)
		return blkg;

	/*
	 * Create blkgs walking down from blkcg_root to @blkcg, so that all
	 * non-root blkgs have access to their parents.
	 */
	while (true) {
		struct blkcg *pos = blkcg;
		struct blkcg *parent = blkcg_parent(blkcg);

		while (parent && !__blkg_lookup(parent, q, false)) {
			pos = parent;
			parent = blkcg_parent(parent);
		}

		blkg = blkg_create(pos, q, NULL);
		if (pos == blkcg || IS_ERR(blkg))
			return blkg;
	}
}