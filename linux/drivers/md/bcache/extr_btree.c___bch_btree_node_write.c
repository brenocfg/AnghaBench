#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct closure {int dummy; } ;
struct btree {scalar_t__ written; TYPE_4__* c; int /*<<< orphan*/  key; int /*<<< orphan*/  flags; int /*<<< orphan*/  io; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  work; int /*<<< orphan*/  keys; int /*<<< orphan*/  write_lock; } ;
struct bset {scalar_t__ seq; int /*<<< orphan*/  keys; } ;
struct TYPE_11__ {int /*<<< orphan*/  btree_sectors_written; } ;
struct TYPE_7__ {int block_size; } ;
struct TYPE_10__ {TYPE_1__ sb; int /*<<< orphan*/  cl; } ;
struct TYPE_9__ {scalar_t__ seq; } ;
struct TYPE_8__ {int bio_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTREE_NODE_dirty ; 
 int /*<<< orphan*/  BTREE_NODE_write_idx ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_5__* PTR_CACHE (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_check_keys (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  block_bytes (TYPE_4__*) ; 
 scalar_t__ btree_blocks (struct btree*) ; 
 TYPE_3__* btree_bset_first (struct btree*) ; 
 struct bset* btree_bset_last (struct btree*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  change_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closure_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  do_btree_node_write (struct btree*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int set_blocks (struct bset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_bcache_btree_write (struct btree*) ; 

void __bch_btree_node_write(struct btree *b, struct closure *parent)
{
	struct bset *i = btree_bset_last(b);

	lockdep_assert_held(&b->write_lock);

	trace_bcache_btree_write(b);

	BUG_ON(current->bio_list);
	BUG_ON(b->written >= btree_blocks(b));
	BUG_ON(b->written && !i->keys);
	BUG_ON(btree_bset_first(b)->seq != i->seq);
	bch_check_keys(&b->keys, "writing");

	cancel_delayed_work(&b->work);

	/* If caller isn't waiting for write, parent refcount is cache set */
	down(&b->io_mutex);
	closure_init(&b->io, parent ?: &b->c->cl);

	clear_bit(BTREE_NODE_dirty,	 &b->flags);
	change_bit(BTREE_NODE_write_idx, &b->flags);

	do_btree_node_write(b);

	atomic_long_add(set_blocks(i, block_bytes(b->c)) * b->c->sb.block_size,
			&PTR_CACHE(b->c, &b->key, 0)->btree_sectors_written);

	b->written += set_blocks(i, block_bytes(b->c));
}