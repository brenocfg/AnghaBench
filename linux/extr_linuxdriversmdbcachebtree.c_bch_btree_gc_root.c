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
struct gc_stat {int dummy; } ;
struct closure {int dummy; } ;
struct btree_op {int dummy; } ;
struct btree {int /*<<< orphan*/  key; TYPE_1__* c; scalar_t__ level; } ;
struct TYPE_2__ {int /*<<< orphan*/  gc_done; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct btree*) ; 
 int /*<<< orphan*/  __bch_btree_mark_key (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_btree_node_write_sync (struct btree*) ; 
 int /*<<< orphan*/  bch_btree_set_root (struct btree*) ; 
 int /*<<< orphan*/  bkey_copy_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int btree_gc_mark_node (struct btree*,struct gc_stat*) ; 
 int btree_gc_recurse (struct btree*,struct btree_op*,struct closure*,struct gc_stat*) ; 
 struct btree* btree_node_alloc_replacement (struct btree*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_node_free (struct btree*) ; 
 int /*<<< orphan*/  rw_unlock (int,struct btree*) ; 

__attribute__((used)) static int bch_btree_gc_root(struct btree *b, struct btree_op *op,
			     struct closure *writes, struct gc_stat *gc)
{
	struct btree *n = NULL;
	int ret = 0;
	bool should_rewrite;

	should_rewrite = btree_gc_mark_node(b, gc);
	if (should_rewrite) {
		n = btree_node_alloc_replacement(b, NULL);

		if (!IS_ERR_OR_NULL(n)) {
			bch_btree_node_write_sync(n);

			bch_btree_set_root(n);
			btree_node_free(b);
			rw_unlock(true, n);

			return -EINTR;
		}
	}

	__bch_btree_mark_key(b->c, b->level + 1, &b->key);

	if (b->level) {
		ret = btree_gc_recurse(b, op, writes, gc);
		if (ret)
			return ret;
	}

	bkey_copy_key(&b->c->gc_done, &b->key);

	return ret;
}