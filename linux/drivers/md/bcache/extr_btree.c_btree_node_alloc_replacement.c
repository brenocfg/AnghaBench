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
struct btree_op {int dummy; } ;
struct btree {int /*<<< orphan*/  write_lock; int /*<<< orphan*/  key; TYPE_1__* c; int /*<<< orphan*/  keys; int /*<<< orphan*/  parent; int /*<<< orphan*/  level; } ;
struct TYPE_2__ {int /*<<< orphan*/  sort; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct btree*) ; 
 struct btree* bch_btree_node_alloc (TYPE_1__*,struct btree_op*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_btree_sort_into (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bkey_copy_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btree *btree_node_alloc_replacement(struct btree *b,
						  struct btree_op *op)
{
	struct btree *n = bch_btree_node_alloc(b->c, op, b->level, b->parent);

	if (!IS_ERR_OR_NULL(n)) {
		mutex_lock(&n->write_lock);
		bch_btree_sort_into(&b->keys, &n->keys, &b->c->sort);
		bkey_copy_key(&n->key, &b->key);
		mutex_unlock(&n->write_lock);
	}

	return n;
}