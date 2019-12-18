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
struct cache_set {int dummy; } ;
struct btree {int /*<<< orphan*/  io_mutex; struct cache_set* c; int /*<<< orphan*/  work; int /*<<< orphan*/  list; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  lock; } ;
struct bkey {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_node_write_work ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct btree* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_novalidate_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mca_data_alloc (struct btree*,struct bkey*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct btree *mca_bucket_alloc(struct cache_set *c,
				      struct bkey *k, gfp_t gfp)
{
	/*
	 * kzalloc() is necessary here for initialization,
	 * see code comments in bch_btree_keys_init().
	 */
	struct btree *b = kzalloc(sizeof(struct btree), gfp);

	if (!b)
		return NULL;

	init_rwsem(&b->lock);
	lockdep_set_novalidate_class(&b->lock);
	mutex_init(&b->write_lock);
	lockdep_set_novalidate_class(&b->write_lock);
	INIT_LIST_HEAD(&b->list);
	INIT_DELAYED_WORK(&b->work, btree_node_write_work);
	b->c = c;
	sema_init(&b->io_mutex, 1);

	mca_data_alloc(b, k, gfp);
	return b;
}