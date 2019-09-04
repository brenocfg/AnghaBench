#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct closure {int dummy; } ;
struct TYPE_11__ {TYPE_2__* set; } ;
struct btree {int /*<<< orphan*/  key; TYPE_4__* c; TYPE_3__ keys; } ;
struct TYPE_9__ {int bi_size; } ;
struct bio {int bi_opf; scalar_t__ bi_status; struct closure* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;
struct TYPE_12__ {int /*<<< orphan*/  btree_read_time; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int KEY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_BUCKET_NR (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int REQ_META ; 
 int REQ_OP_READ ; 
 struct bio* bch_bbio_alloc (TYPE_4__*) ; 
 int /*<<< orphan*/  bch_bbio_free (struct bio*,TYPE_4__*) ; 
 int /*<<< orphan*/  bch_bio_map (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_btree_node_read_done (struct btree*) ; 
 int /*<<< orphan*/  bch_cache_set_error (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_submit_bbio (struct bio*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_time_stats_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ btree_node_io_error (struct btree*) ; 
 int /*<<< orphan*/  btree_node_read_endio ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  local_clock () ; 
 int /*<<< orphan*/  set_btree_node_io_error (struct btree*) ; 
 int /*<<< orphan*/  trace_bcache_btree_read (struct btree*) ; 

__attribute__((used)) static void bch_btree_node_read(struct btree *b)
{
	uint64_t start_time = local_clock();
	struct closure cl;
	struct bio *bio;

	trace_bcache_btree_read(b);

	closure_init_stack(&cl);

	bio = bch_bbio_alloc(b->c);
	bio->bi_iter.bi_size = KEY_SIZE(&b->key) << 9;
	bio->bi_end_io	= btree_node_read_endio;
	bio->bi_private	= &cl;
	bio->bi_opf = REQ_OP_READ | REQ_META;

	bch_bio_map(bio, b->keys.set[0].data);

	bch_submit_bbio(bio, b->c, &b->key, 0);
	closure_sync(&cl);

	if (bio->bi_status)
		set_btree_node_io_error(b);

	bch_bbio_free(bio, b->c);

	if (btree_node_io_error(b))
		goto err;

	bch_btree_node_read_done(b);
	bch_time_stats_update(&b->c->btree_read_time, start_time);

	return;
err:
	bch_cache_set_error(b->c, "io error reading bucket %zu",
			    PTR_BUCKET_NR(b->c, &b->key, 0));
}