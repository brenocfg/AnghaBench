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
struct cache_set {int /*<<< orphan*/  bucket_lock; } ;
struct btree_op {int dummy; } ;
struct TYPE_5__ {int nsets; TYPE_1__* set; } ;
struct bkey {int dummy; } ;
struct btree {int level; int accessed; TYPE_2__ keys; struct btree* parent; int /*<<< orphan*/  written; struct bkey key; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {scalar_t__ bio_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  tree; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 struct btree* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct btree*) ; 
 scalar_t__ PTR_HASH (struct cache_set*,struct bkey*) ; 
 int /*<<< orphan*/  bch_btree_node_read (struct btree*) ; 
 scalar_t__ btree_node_io_error (struct btree*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 struct btree* mca_alloc (struct cache_set*,struct btree_op*,struct bkey*,int) ; 
 struct btree* mca_find (struct cache_set*,struct bkey*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_lock (int,struct btree*,int) ; 
 int /*<<< orphan*/  rw_unlock (int,struct btree*) ; 

struct btree *bch_btree_node_get(struct cache_set *c, struct btree_op *op,
				 struct bkey *k, int level, bool write,
				 struct btree *parent)
{
	int i = 0;
	struct btree *b;

	BUG_ON(level < 0);
retry:
	b = mca_find(c, k);

	if (!b) {
		if (current->bio_list)
			return ERR_PTR(-EAGAIN);

		mutex_lock(&c->bucket_lock);
		b = mca_alloc(c, op, k, level);
		mutex_unlock(&c->bucket_lock);

		if (!b)
			goto retry;
		if (IS_ERR(b))
			return b;

		bch_btree_node_read(b);

		if (!write)
			downgrade_write(&b->lock);
	} else {
		rw_lock(write, b, level);
		if (PTR_HASH(c, &b->key) != PTR_HASH(c, k)) {
			rw_unlock(write, b);
			goto retry;
		}
		BUG_ON(b->level != level);
	}

	if (btree_node_io_error(b)) {
		rw_unlock(write, b);
		return ERR_PTR(-EIO);
	}

	BUG_ON(!b->written);

	b->parent = parent;
	b->accessed = 1;

	for (; i <= b->keys.nsets && b->keys.set[i].size; i++) {
		prefetch(b->keys.set[i].tree);
		prefetch(b->keys.set[i].data);
	}

	for (; i <= b->keys.nsets; i++)
		prefetch(b->keys.set[i].data);

	return b;
}