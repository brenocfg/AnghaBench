#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct closure {int dummy; } ;
struct btree {TYPE_1__* c; int /*<<< orphan*/  list; int /*<<< orphan*/  key; int /*<<< orphan*/  written; } ;
struct TYPE_5__ {scalar_t__ prio; } ;
struct TYPE_4__ {struct btree* root; int /*<<< orphan*/  bucket_lock; } ;

/* Variables and functions */
 scalar_t__ BTREE_PRIO ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int KEY_PTRS (int /*<<< orphan*/ *) ; 
 TYPE_2__* PTR_BUCKET (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  bch_journal_meta (TYPE_1__*,struct closure*) ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_bcache_btree_set_root (struct btree*) ; 

void bch_btree_set_root(struct btree *b)
{
	unsigned int i;
	struct closure cl;

	closure_init_stack(&cl);

	trace_bcache_btree_set_root(b);

	BUG_ON(!b->written);

	for (i = 0; i < KEY_PTRS(&b->key); i++)
		BUG_ON(PTR_BUCKET(b->c, &b->key, i)->prio != BTREE_PRIO);

	mutex_lock(&b->c->bucket_lock);
	list_del_init(&b->list);
	mutex_unlock(&b->c->bucket_lock);

	b->c->root = b;

	bch_journal_meta(b->c, &cl);
	closure_sync(&cl);
}