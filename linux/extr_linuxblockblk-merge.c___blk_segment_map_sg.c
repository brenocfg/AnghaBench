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
struct scatterlist {scalar_t__ length; } ;
struct request_queue {int dummy; } ;
struct bio_vec {int bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOVEC_PHYS_MERGEABLE (struct bio_vec*,struct bio_vec*) ; 
 int /*<<< orphan*/  BIOVEC_SEG_BOUNDARY (struct request_queue*,struct bio_vec*,struct bio_vec*) ; 
 scalar_t__ queue_max_segment_size (struct request_queue*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 

__attribute__((used)) static inline void
__blk_segment_map_sg(struct request_queue *q, struct bio_vec *bvec,
		     struct scatterlist *sglist, struct bio_vec *bvprv,
		     struct scatterlist **sg, int *nsegs, int *cluster)
{

	int nbytes = bvec->bv_len;

	if (*sg && *cluster) {
		if ((*sg)->length + nbytes > queue_max_segment_size(q))
			goto new_segment;

		if (!BIOVEC_PHYS_MERGEABLE(bvprv, bvec))
			goto new_segment;
		if (!BIOVEC_SEG_BOUNDARY(q, bvprv, bvec))
			goto new_segment;

		(*sg)->length += nbytes;
	} else {
new_segment:
		if (!*sg)
			*sg = sglist;
		else {
			/*
			 * If the driver previously mapped a shorter
			 * list, we could see a termination bit
			 * prematurely unless it fully inits the sg
			 * table on each mapping. We KNOW that there
			 * must be more entries here or the driver
			 * would be buggy, so force clear the
			 * termination bit to avoid doing a full
			 * sg_init_table() in drivers for each command.
			 */
			sg_unmark_end(*sg);
			*sg = sg_next(*sg);
		}

		sg_set_page(*sg, bvec->bv_page, nbytes, bvec->bv_offset);
		(*nsegs)++;
	}
	*bvprv = *bvec;
}