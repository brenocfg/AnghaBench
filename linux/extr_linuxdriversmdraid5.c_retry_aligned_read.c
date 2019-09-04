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
struct stripe_head {TYPE_2__* dev; } ;
struct r5conf {int retry_read_offset; int /*<<< orphan*/  wait_for_quiescent; int /*<<< orphan*/  active_aligned_reads; struct bio* retry_read_aligned; } ;
struct TYPE_3__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5_ReadNoMerge ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  add_stripe_bio (struct stripe_head*,struct bio*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  handle_stripe (struct stripe_head*) ; 
 int raid5_compute_sector (struct r5conf*,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 struct stripe_head* raid5_get_active_stripe (struct r5conf*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  raid5_release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int  retry_aligned_read(struct r5conf *conf, struct bio *raid_bio,
			       unsigned int offset)
{
	/* We may not be able to submit a whole bio at once as there
	 * may not be enough stripe_heads available.
	 * We cannot pre-allocate enough stripe_heads as we may need
	 * more than exist in the cache (if we allow ever large chunks).
	 * So we do one stripe head at a time and record in
	 * ->bi_hw_segments how many have been done.
	 *
	 * We *know* that this entire raid_bio is in one chunk, so
	 * it will be only one 'dd_idx' and only need one call to raid5_compute_sector.
	 */
	struct stripe_head *sh;
	int dd_idx;
	sector_t sector, logical_sector, last_sector;
	int scnt = 0;
	int handled = 0;

	logical_sector = raid_bio->bi_iter.bi_sector &
		~((sector_t)STRIPE_SECTORS-1);
	sector = raid5_compute_sector(conf, logical_sector,
				      0, &dd_idx, NULL);
	last_sector = bio_end_sector(raid_bio);

	for (; logical_sector < last_sector;
	     logical_sector += STRIPE_SECTORS,
		     sector += STRIPE_SECTORS,
		     scnt++) {

		if (scnt < offset)
			/* already done this stripe */
			continue;

		sh = raid5_get_active_stripe(conf, sector, 0, 1, 1);

		if (!sh) {
			/* failed to get a stripe - must wait */
			conf->retry_read_aligned = raid_bio;
			conf->retry_read_offset = scnt;
			return handled;
		}

		if (!add_stripe_bio(sh, raid_bio, dd_idx, 0, 0)) {
			raid5_release_stripe(sh);
			conf->retry_read_aligned = raid_bio;
			conf->retry_read_offset = scnt;
			return handled;
		}

		set_bit(R5_ReadNoMerge, &sh->dev[dd_idx].flags);
		handle_stripe(sh);
		raid5_release_stripe(sh);
		handled++;
	}

	bio_endio(raid_bio);

	if (atomic_dec_and_test(&conf->active_aligned_reads))
		wake_up(&conf->wait_for_quiescent);
	return handled;
}