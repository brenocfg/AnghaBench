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
struct TYPE_2__ {int n_sectors; int logical_sector; } ;
struct dm_integrity_io {int write; int bi_status; int /*<<< orphan*/  work; TYPE_1__ range; struct dm_integrity_c* ic; int /*<<< orphan*/  in_flight; } ;
struct dm_integrity_c {int /*<<< orphan*/  wait_wq; } ;
struct bio {int bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SECTOR_SHIFT ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_advance (struct bio*,int) ; 
 int bio_sectors (struct bio*) ; 
 struct bio* dm_bio_from_per_bio_data (struct dm_integrity_io*,int) ; 
 int /*<<< orphan*/  do_endio_flush (struct dm_integrity_c*,struct dm_integrity_io*) ; 
 int /*<<< orphan*/  integrity_bio_wait ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_range (struct dm_integrity_c*,TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_autocommit (struct dm_integrity_c*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dec_in_flight(struct dm_integrity_io *dio)
{
	if (atomic_dec_and_test(&dio->in_flight)) {
		struct dm_integrity_c *ic = dio->ic;
		struct bio *bio;

		remove_range(ic, &dio->range);

		if (unlikely(dio->write))
			schedule_autocommit(ic);

		bio = dm_bio_from_per_bio_data(dio, sizeof(struct dm_integrity_io));

		if (unlikely(dio->bi_status) && !bio->bi_status)
			bio->bi_status = dio->bi_status;
		if (likely(!bio->bi_status) && unlikely(bio_sectors(bio) != dio->range.n_sectors)) {
			dio->range.logical_sector += dio->range.n_sectors;
			bio_advance(bio, dio->range.n_sectors << SECTOR_SHIFT);
			INIT_WORK(&dio->work, integrity_bio_wait);
			queue_work(ic->wait_wq, &dio->work);
			return;
		}
		do_endio_flush(ic, dio);
	}
}