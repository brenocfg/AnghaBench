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
typedef  int uint64_t ;
struct closure {int dummy; } ;
struct TYPE_3__ {int bucket_size; } ;
struct cache {struct closure prio; int /*<<< orphan*/  set; int /*<<< orphan*/  disk_buckets; int /*<<< orphan*/  bdev; TYPE_1__ sb; } ;
struct TYPE_4__ {int bi_sector; int /*<<< orphan*/  bi_size; } ;
struct bio {struct cache* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_2__ bi_iter; } ;

/* Variables and functions */
 unsigned long REQ_META ; 
 unsigned long REQ_SYNC ; 
 struct bio* bch_bbio_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_bio_map (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,unsigned long) ; 
 int /*<<< orphan*/  bucket_bytes (struct cache*) ; 
 int /*<<< orphan*/  closure_bio_submit (int /*<<< orphan*/ ,struct bio*,struct closure*) ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  prio_endio ; 

__attribute__((used)) static void prio_io(struct cache *ca, uint64_t bucket, int op,
		    unsigned long op_flags)
{
	struct closure *cl = &ca->prio;
	struct bio *bio = bch_bbio_alloc(ca->set);

	closure_init_stack(cl);

	bio->bi_iter.bi_sector	= bucket * ca->sb.bucket_size;
	bio_set_dev(bio, ca->bdev);
	bio->bi_iter.bi_size	= bucket_bytes(ca);

	bio->bi_end_io	= prio_endio;
	bio->bi_private = ca;
	bio_set_op_attrs(bio, op, REQ_SYNC|REQ_META|op_flags);
	bch_bio_map(bio, ca->disk_buckets);

	closure_bio_submit(ca->set, bio, &ca->prio);
	closure_sync(cl);
}