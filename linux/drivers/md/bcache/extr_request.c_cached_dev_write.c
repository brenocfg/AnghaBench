#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int bypass; int writeback; int /*<<< orphan*/  cl; TYPE_5__* c; struct bio* bio; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; void* bi_end_io; struct closure* bi_private; TYPE_2__ bi_iter; } ;
struct TYPE_6__ {struct bio bio; } ;
struct closure {int dummy; } ;
struct search {TYPE_4__ iop; struct bio* orig_bio; TYPE_1__ bio; struct closure cl; } ;
struct TYPE_8__ {int /*<<< orphan*/  bio_split; int /*<<< orphan*/  id; } ;
struct cached_dev {TYPE_3__ disk; int /*<<< orphan*/  bdev; int /*<<< orphan*/  writeback_keys; int /*<<< orphan*/  writeback_lock; } ;
struct bkey {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  moving_gc_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 struct bkey KEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 void* backing_request_endio ; 
 int /*<<< orphan*/  bch_data_insert ; 
 scalar_t__ bch_keybuf_check_overlapping (int /*<<< orphan*/ *,struct bkey*,struct bkey*) ; 
 int /*<<< orphan*/  bch_writeback_add (struct cached_dev*) ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_copy_dev (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_mode (struct cached_dev*) ; 
 int /*<<< orphan*/  cached_dev_write_complete ; 
 int /*<<< orphan*/  closure_bio_submit (TYPE_5__*,struct bio*,struct closure*) ; 
 int /*<<< orphan*/  closure_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct closure*) ; 
 int /*<<< orphan*/  continue_at (struct closure*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_non_owner (int /*<<< orphan*/ *) ; 
 scalar_t__ should_writeback (struct cached_dev*,struct bio*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cached_dev_write(struct cached_dev *dc, struct search *s)
{
	struct closure *cl = &s->cl;
	struct bio *bio = &s->bio.bio;
	struct bkey start = KEY(dc->disk.id, bio->bi_iter.bi_sector, 0);
	struct bkey end = KEY(dc->disk.id, bio_end_sector(bio), 0);

	bch_keybuf_check_overlapping(&s->iop.c->moving_gc_keys, &start, &end);

	down_read_non_owner(&dc->writeback_lock);
	if (bch_keybuf_check_overlapping(&dc->writeback_keys, &start, &end)) {
		/*
		 * We overlap with some dirty data undergoing background
		 * writeback, force this write to writeback
		 */
		s->iop.bypass = false;
		s->iop.writeback = true;
	}

	/*
	 * Discards aren't _required_ to do anything, so skipping if
	 * check_overlapping returned true is ok
	 *
	 * But check_overlapping drops dirty keys for which io hasn't started,
	 * so we still want to call it.
	 */
	if (bio_op(bio) == REQ_OP_DISCARD)
		s->iop.bypass = true;

	if (should_writeback(dc, s->orig_bio,
			     cache_mode(dc),
			     s->iop.bypass)) {
		s->iop.bypass = false;
		s->iop.writeback = true;
	}

	if (s->iop.bypass) {
		s->iop.bio = s->orig_bio;
		bio_get(s->iop.bio);

		if (bio_op(bio) == REQ_OP_DISCARD &&
		    !blk_queue_discard(bdev_get_queue(dc->bdev)))
			goto insert_data;

		/* I/O request sent to backing device */
		bio->bi_end_io = backing_request_endio;
		closure_bio_submit(s->iop.c, bio, cl);

	} else if (s->iop.writeback) {
		bch_writeback_add(dc);
		s->iop.bio = bio;

		if (bio->bi_opf & REQ_PREFLUSH) {
			/*
			 * Also need to send a flush to the backing
			 * device.
			 */
			struct bio *flush;

			flush = bio_alloc_bioset(GFP_NOIO, 0,
						 &dc->disk.bio_split);
			if (!flush) {
				s->iop.status = BLK_STS_RESOURCE;
				goto insert_data;
			}
			bio_copy_dev(flush, bio);
			flush->bi_end_io = backing_request_endio;
			flush->bi_private = cl;
			flush->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
			/* I/O request sent to backing device */
			closure_bio_submit(s->iop.c, flush, cl);
		}
	} else {
		s->iop.bio = bio_clone_fast(bio, GFP_NOIO, &dc->disk.bio_split);
		/* I/O request sent to backing device */
		bio->bi_end_io = backing_request_endio;
		closure_bio_submit(s->iop.c, bio, cl);
	}

insert_data:
	closure_call(&s->iop.cl, bch_data_insert, NULL, cl);
	continue_at(cl, cached_dev_write_complete, NULL);
}