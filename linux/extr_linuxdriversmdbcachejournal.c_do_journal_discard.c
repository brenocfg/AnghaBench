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
struct TYPE_5__ {int /*<<< orphan*/  bi_size; int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_end_io; TYPE_2__ bi_iter; int /*<<< orphan*/  bi_inline_vecs; } ;
struct journal_device {int discard_idx; int last_idx; int /*<<< orphan*/  discard_work; int /*<<< orphan*/  discard_in_flight; struct bio discard_bio; } ;
struct TYPE_4__ {int njournal_buckets; int /*<<< orphan*/ * d; } ;
struct cache {TYPE_3__* set; int /*<<< orphan*/  bdev; TYPE_1__ sb; int /*<<< orphan*/  discard; struct journal_device journal; } ;
struct TYPE_6__ {int /*<<< orphan*/  cl; } ;

/* Variables and functions */
#define  DISCARD_DONE 130 
#define  DISCARD_IN_FLIGHT 129 
#define  DISCARD_READY 128 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_OP_DISCARD ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  bch_journal_wq ; 
 int /*<<< orphan*/  bio_init (struct bio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bucket_bytes (struct cache*) ; 
 int /*<<< orphan*/  bucket_to_sector (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closure_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_discard_endio ; 
 int /*<<< orphan*/  journal_discard_work ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_journal_discard(struct cache *ca)
{
	struct journal_device *ja = &ca->journal;
	struct bio *bio = &ja->discard_bio;

	if (!ca->discard) {
		ja->discard_idx = ja->last_idx;
		return;
	}

	switch (atomic_read(&ja->discard_in_flight)) {
	case DISCARD_IN_FLIGHT:
		return;

	case DISCARD_DONE:
		ja->discard_idx = (ja->discard_idx + 1) %
			ca->sb.njournal_buckets;

		atomic_set(&ja->discard_in_flight, DISCARD_READY);
		/* fallthrough */

	case DISCARD_READY:
		if (ja->discard_idx == ja->last_idx)
			return;

		atomic_set(&ja->discard_in_flight, DISCARD_IN_FLIGHT);

		bio_init(bio, bio->bi_inline_vecs, 1);
		bio_set_op_attrs(bio, REQ_OP_DISCARD, 0);
		bio->bi_iter.bi_sector	= bucket_to_sector(ca->set,
						ca->sb.d[ja->discard_idx]);
		bio_set_dev(bio, ca->bdev);
		bio->bi_iter.bi_size	= bucket_bytes(ca);
		bio->bi_end_io		= journal_discard_endio;

		closure_get(&ca->set->cl);
		INIT_WORK(&ja->discard_work, journal_discard_work);
		queue_work(bch_journal_wq, &ja->discard_work);
	}
}