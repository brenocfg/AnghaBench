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
typedef  size_t uint32_t ;
struct stripe_c {unsigned int stripes; TYPE_3__* stripe; } ;
struct dm_target {struct stripe_c* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_1__ bi_iter; } ;
struct TYPE_6__ {TYPE_2__* dev; scalar_t__ physical_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DM_MAPIO_REMAPPED ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_SECURE_ERASE ; 
 scalar_t__ REQ_OP_WRITE_SAME ; 
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 int REQ_PREFLUSH ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 unsigned int dm_bio_get_target_bio_nr (struct bio*) ; 
 int stripe_map_range (struct stripe_c*,struct bio*,unsigned int) ; 
 int /*<<< orphan*/  stripe_map_sector (struct stripe_c*,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int stripe_map(struct dm_target *ti, struct bio *bio)
{
	struct stripe_c *sc = ti->private;
	uint32_t stripe;
	unsigned target_bio_nr;

	if (bio->bi_opf & REQ_PREFLUSH) {
		target_bio_nr = dm_bio_get_target_bio_nr(bio);
		BUG_ON(target_bio_nr >= sc->stripes);
		bio_set_dev(bio, sc->stripe[target_bio_nr].dev->bdev);
		return DM_MAPIO_REMAPPED;
	}
	if (unlikely(bio_op(bio) == REQ_OP_DISCARD) ||
	    unlikely(bio_op(bio) == REQ_OP_SECURE_ERASE) ||
	    unlikely(bio_op(bio) == REQ_OP_WRITE_ZEROES) ||
	    unlikely(bio_op(bio) == REQ_OP_WRITE_SAME)) {
		target_bio_nr = dm_bio_get_target_bio_nr(bio);
		BUG_ON(target_bio_nr >= sc->stripes);
		return stripe_map_range(sc, bio, target_bio_nr);
	}

	stripe_map_sector(sc, bio->bi_iter.bi_sector,
			  &stripe, &bio->bi_iter.bi_sector);

	bio->bi_iter.bi_sector += sc->stripe[stripe].physical_start;
	bio_set_dev(bio, sc->stripe[stripe].dev->bdev);

	return DM_MAPIO_REMAPPED;
}