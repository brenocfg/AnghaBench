#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bio {int /*<<< orphan*/  bi_end_io; } ;
struct TYPE_4__ {struct bio bio; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; struct cache_set* c; int /*<<< orphan*/  inode; } ;
struct moving_io {int /*<<< orphan*/  cl; TYPE_2__ bio; TYPE_1__ op; struct keybuf_key* w; } ;
struct keybuf_key {struct moving_io* private; int /*<<< orphan*/  key; } ;
struct closure {int dummy; } ;
struct cache_set {int /*<<< orphan*/  moving_gc_keys; int /*<<< orphan*/  moving_in_flight; int /*<<< orphan*/  moving_gc_wq; int /*<<< orphan*/  flags; } ;
struct bio_vec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SET_STOPPING ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct moving_io*) ; 
 int /*<<< orphan*/  KEY_INODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_KEY ; 
 int /*<<< orphan*/  PAGE_SECTORS ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ bch_bio_alloc_pages (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_keybuf_del (int /*<<< orphan*/ *,struct keybuf_key*) ; 
 struct keybuf_key* bch_keybuf_next_rescan (struct cache_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closure_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct closure*) ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct moving_io*) ; 
 struct moving_io* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moving_init (struct moving_io*) ; 
 int /*<<< orphan*/  moving_pred ; 
 scalar_t__ ptr_stale (struct cache_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_moving_endio ; 
 int /*<<< orphan*/  read_moving_submit ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_bcache_gc_copy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_moving(struct cache_set *c)
{
	struct keybuf_key *w;
	struct moving_io *io;
	struct bio *bio;
	struct closure cl;

	closure_init_stack(&cl);

	/* XXX: if we error, background writeback could stall indefinitely */

	while (!test_bit(CACHE_SET_STOPPING, &c->flags)) {
		w = bch_keybuf_next_rescan(c, &c->moving_gc_keys,
					   &MAX_KEY, moving_pred);
		if (!w)
			break;

		if (ptr_stale(c, &w->key, 0)) {
			bch_keybuf_del(&c->moving_gc_keys, w);
			continue;
		}

		io = kzalloc(sizeof(struct moving_io) + sizeof(struct bio_vec)
			     * DIV_ROUND_UP(KEY_SIZE(&w->key), PAGE_SECTORS),
			     GFP_KERNEL);
		if (!io)
			goto err;

		w->private	= io;
		io->w		= w;
		io->op.inode	= KEY_INODE(&w->key);
		io->op.c	= c;
		io->op.wq	= c->moving_gc_wq;

		moving_init(io);
		bio = &io->bio.bio;

		bio_set_op_attrs(bio, REQ_OP_READ, 0);
		bio->bi_end_io	= read_moving_endio;

		if (bch_bio_alloc_pages(bio, GFP_KERNEL))
			goto err;

		trace_bcache_gc_copy(&w->key);

		down(&c->moving_in_flight);
		closure_call(&io->cl, read_moving_submit, NULL, &cl);
	}

	if (0) {
err:		if (!IS_ERR_OR_NULL(w->private))
			kfree(w->private);

		bch_keybuf_del(&c->moving_gc_keys, w);
	}

	closure_sync(&cl);
}