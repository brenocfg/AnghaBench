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
struct request_queue {int dummy; } ;
struct page {int dummy; } ;
struct bio_vec {unsigned int bv_offset; unsigned int bv_len; struct page* bv_page; } ;
struct TYPE_2__ {unsigned int bi_size; } ;
struct bio {int bi_vcnt; scalar_t__ bi_phys_segments; TYPE_1__ bi_iter; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 scalar_t__ BIOVEC_PHYS_MERGEABLE (struct bio_vec*,struct bio_vec*) ; 
 int /*<<< orphan*/  BIO_CLONED ; 
 int /*<<< orphan*/  BIO_SEG_VALID ; 
 int /*<<< orphan*/  bio_clear_flag (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_full (struct bio*) ; 
 int /*<<< orphan*/  blk_recount_segments (struct request_queue*,struct bio*) ; 
 scalar_t__ bvec_gap_to_prev (struct request_queue*,struct bio_vec*,unsigned int) ; 
 unsigned int queue_max_hw_sectors (struct request_queue*) ; 
 scalar_t__ queue_max_segments (struct request_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int bio_add_pc_page(struct request_queue *q, struct bio *bio, struct page
		    *page, unsigned int len, unsigned int offset)
{
	int retried_segments = 0;
	struct bio_vec *bvec;

	/*
	 * cloned bio must not modify vec list
	 */
	if (unlikely(bio_flagged(bio, BIO_CLONED)))
		return 0;

	if (((bio->bi_iter.bi_size + len) >> 9) > queue_max_hw_sectors(q))
		return 0;

	/*
	 * For filesystems with a blocksize smaller than the pagesize
	 * we will often be called with the same page as last time and
	 * a consecutive offset.  Optimize this special case.
	 */
	if (bio->bi_vcnt > 0) {
		struct bio_vec *prev = &bio->bi_io_vec[bio->bi_vcnt - 1];

		if (page == prev->bv_page &&
		    offset == prev->bv_offset + prev->bv_len) {
			prev->bv_len += len;
			bio->bi_iter.bi_size += len;
			goto done;
		}

		/*
		 * If the queue doesn't support SG gaps and adding this
		 * offset would create a gap, disallow it.
		 */
		if (bvec_gap_to_prev(q, prev, offset))
			return 0;
	}

	if (bio_full(bio))
		return 0;

	/*
	 * setup the new entry, we might clear it again later if we
	 * cannot add the page
	 */
	bvec = &bio->bi_io_vec[bio->bi_vcnt];
	bvec->bv_page = page;
	bvec->bv_len = len;
	bvec->bv_offset = offset;
	bio->bi_vcnt++;
	bio->bi_phys_segments++;
	bio->bi_iter.bi_size += len;

	/*
	 * Perform a recount if the number of segments is greater
	 * than queue_max_segments(q).
	 */

	while (bio->bi_phys_segments > queue_max_segments(q)) {

		if (retried_segments)
			goto failed;

		retried_segments = 1;
		blk_recount_segments(q, bio);
	}

	/* If we may be able to merge these biovecs, force a recount */
	if (bio->bi_vcnt > 1 && (BIOVEC_PHYS_MERGEABLE(bvec-1, bvec)))
		bio_clear_flag(bio, BIO_SEG_VALID);

 done:
	return len;

 failed:
	bvec->bv_page = NULL;
	bvec->bv_len = 0;
	bvec->bv_offset = 0;
	bio->bi_vcnt--;
	bio->bi_iter.bi_size -= len;
	blk_recount_segments(q, bio);
	return 0;
}