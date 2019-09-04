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
struct request_queue {int dummy; } ;
struct bio_vec {int /*<<< orphan*/ * member_0; } ;
struct bio {scalar_t__ bi_seg_back_size; scalar_t__ bi_seg_front_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOVEC_PHYS_MERGEABLE (struct bio_vec*,struct bio_vec*) ; 
 scalar_t__ BIOVEC_SEG_BOUNDARY (struct request_queue*,struct bio_vec*,struct bio_vec*) ; 
 int /*<<< orphan*/  bio_get_first_bvec (struct bio*,struct bio_vec*) ; 
 int /*<<< orphan*/  bio_get_last_bvec (struct bio*,struct bio_vec*) ; 
 int /*<<< orphan*/  bio_has_data (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_cluster (struct request_queue*) ; 
 scalar_t__ queue_max_segment_size (struct request_queue*) ; 

__attribute__((used)) static int blk_phys_contig_segment(struct request_queue *q, struct bio *bio,
				   struct bio *nxt)
{
	struct bio_vec end_bv = { NULL }, nxt_bv;

	if (!blk_queue_cluster(q))
		return 0;

	if (bio->bi_seg_back_size + nxt->bi_seg_front_size >
	    queue_max_segment_size(q))
		return 0;

	if (!bio_has_data(bio))
		return 1;

	bio_get_last_bvec(bio, &end_bv);
	bio_get_first_bvec(nxt, &nxt_bv);

	if (!BIOVEC_PHYS_MERGEABLE(&end_bv, &nxt_bv))
		return 0;

	/*
	 * bio and nxt are contiguous in memory; check if the queue allows
	 * these two to be merged into one
	 */
	if (BIOVEC_SEG_BOUNDARY(q, &end_bv, &nxt_bv))
		return 1;

	return 0;
}