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
struct btree {struct btree* parent; TYPE_1__* c; scalar_t__ level; } ;
struct bkey {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bucket_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct btree*) ; 
 int /*<<< orphan*/  bch_btree_node_read (struct btree*) ; 
 struct btree* mca_alloc (TYPE_1__*,int /*<<< orphan*/ *,struct bkey*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_unlock (int,struct btree*) ; 

__attribute__((used)) static void btree_node_prefetch(struct btree *parent, struct bkey *k)
{
	struct btree *b;

	mutex_lock(&parent->c->bucket_lock);
	b = mca_alloc(parent->c, NULL, k, parent->level - 1);
	mutex_unlock(&parent->c->bucket_lock);

	if (!IS_ERR_OR_NULL(b)) {
		b->parent = parent;
		bch_btree_node_read(b);
		rw_unlock(true, b);
	}
}