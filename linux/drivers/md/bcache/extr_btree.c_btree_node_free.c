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
struct btree {TYPE_1__* c; int /*<<< orphan*/  key; int /*<<< orphan*/  work; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  bucket_lock; struct btree* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTREE_NODE_dirty ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bch_bucket_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_complete_write (struct btree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btree_current_write (struct btree*) ; 
 scalar_t__ btree_node_dirty (struct btree*) ; 
 scalar_t__ btree_node_journal_flush (struct btree*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mca_bucket_free (struct btree*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct btree*) ; 
 int /*<<< orphan*/  trace_bcache_btree_node_free (struct btree*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void btree_node_free(struct btree *b)
{
	trace_bcache_btree_node_free(b);

	BUG_ON(b == b->c->root);

retry:
	mutex_lock(&b->write_lock);
	/*
	 * If the btree node is selected and flushing in btree_flush_write(),
	 * delay and retry until the BTREE_NODE_journal_flush bit cleared,
	 * then it is safe to free the btree node here. Otherwise this btree
	 * node will be in race condition.
	 */
	if (btree_node_journal_flush(b)) {
		mutex_unlock(&b->write_lock);
		pr_debug("bnode %p journal_flush set, retry", b);
		udelay(1);
		goto retry;
	}

	if (btree_node_dirty(b)) {
		btree_complete_write(b, btree_current_write(b));
		clear_bit(BTREE_NODE_dirty, &b->flags);
	}

	mutex_unlock(&b->write_lock);

	cancel_delayed_work(&b->work);

	mutex_lock(&b->c->bucket_lock);
	bch_bucket_free(b->c, &b->key);
	mca_bucket_free(b);
	mutex_unlock(&b->c->bucket_lock);
}