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
struct dmz_target {int /*<<< orphan*/  metadata; TYPE_1__* dev; int /*<<< orphan*/  bio_set; } ;
struct dmz_bioctx {int /*<<< orphan*/  ref; } ;
struct dm_zone {unsigned int wp_block; } ;
struct TYPE_4__ {int bi_size; scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; struct dmz_bioctx* bi_private; int /*<<< orphan*/  bi_end_io; } ;
typedef  unsigned int sector_t ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ REQ_OP_WRITE ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  bio_advance (struct bio*,int) ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 struct dmz_bioctx* dm_per_bio_data (struct bio*,int) ; 
 int dmz_blk2sect (unsigned int) ; 
 int /*<<< orphan*/  dmz_clone_endio ; 
 scalar_t__ dmz_is_seq (struct dm_zone*) ; 
 scalar_t__ dmz_start_sect (int /*<<< orphan*/ ,struct dm_zone*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmz_submit_bio(struct dmz_target *dmz, struct dm_zone *zone,
			  struct bio *bio, sector_t chunk_block,
			  unsigned int nr_blocks)
{
	struct dmz_bioctx *bioctx = dm_per_bio_data(bio, sizeof(struct dmz_bioctx));
	struct bio *clone;

	clone = bio_clone_fast(bio, GFP_NOIO, &dmz->bio_set);
	if (!clone)
		return -ENOMEM;

	bio_set_dev(clone, dmz->dev->bdev);
	clone->bi_iter.bi_sector =
		dmz_start_sect(dmz->metadata, zone) + dmz_blk2sect(chunk_block);
	clone->bi_iter.bi_size = dmz_blk2sect(nr_blocks) << SECTOR_SHIFT;
	clone->bi_end_io = dmz_clone_endio;
	clone->bi_private = bioctx;

	bio_advance(bio, clone->bi_iter.bi_size);

	refcount_inc(&bioctx->ref);
	generic_make_request(clone);

	if (bio_op(bio) == REQ_OP_WRITE && dmz_is_seq(zone))
		zone->wp_block += nr_blocks;

	return 0;
}