#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct closure {int dummy; } ;
struct TYPE_6__ {unsigned int page_order; TYPE_2__* set; } ;
struct btree {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  write_lock; TYPE_3__ keys; int /*<<< orphan*/  lock; TYPE_1__* c; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  bucket_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __bch_btree_node_write (struct btree*,struct closure*) ; 
 scalar_t__ btree_node_dirty (struct btree*) ; 
 scalar_t__ btree_node_journal_flush (struct btree*) ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct btree*) ; 
 int /*<<< orphan*/  rw_unlock (int,struct btree*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mca_reap(struct btree *b, unsigned int min_order, bool flush)
{
	struct closure cl;

	closure_init_stack(&cl);
	lockdep_assert_held(&b->c->bucket_lock);

	if (!down_write_trylock(&b->lock))
		return -ENOMEM;

	BUG_ON(btree_node_dirty(b) && !b->keys.set[0].data);

	if (b->keys.page_order < min_order)
		goto out_unlock;

	if (!flush) {
		if (btree_node_dirty(b))
			goto out_unlock;

		if (down_trylock(&b->io_mutex))
			goto out_unlock;
		up(&b->io_mutex);
	}

retry:
	/*
	 * BTREE_NODE_dirty might be cleared in btree_flush_btree() by
	 * __bch_btree_node_write(). To avoid an extra flush, acquire
	 * b->write_lock before checking BTREE_NODE_dirty bit.
	 */
	mutex_lock(&b->write_lock);
	/*
	 * If this btree node is selected in btree_flush_write() by journal
	 * code, delay and retry until the node is flushed by journal code
	 * and BTREE_NODE_journal_flush bit cleared by btree_flush_write().
	 */
	if (btree_node_journal_flush(b)) {
		pr_debug("bnode %p is flushing by journal, retry", b);
		mutex_unlock(&b->write_lock);
		udelay(1);
		goto retry;
	}

	if (btree_node_dirty(b))
		__bch_btree_node_write(b, &cl);
	mutex_unlock(&b->write_lock);

	closure_sync(&cl);

	/* wait for any in flight btree write */
	down(&b->io_mutex);
	up(&b->io_mutex);

	return 0;
out_unlock:
	rw_unlock(true, b);
	return -ENOMEM;
}