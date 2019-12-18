#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct r1conf {TYPE_3__* mddev; TYPE_1__* mirrors; } ;
struct r1bio {int /*<<< orphan*/ ** bios; struct bio* master_bio; int /*<<< orphan*/  state; int /*<<< orphan*/  remaining; int /*<<< orphan*/  behind_remaining; scalar_t__ sectors; scalar_t__ sector; TYPE_4__* mddev; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ bi_sector; } ;
struct bio {int bi_opf; TYPE_2__ bi_iter; scalar_t__ bi_status; struct r1bio* bi_private; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_8__ {struct r1conf* private; } ;
struct TYPE_7__ {int /*<<< orphan*/  recovery; } ;
struct TYPE_5__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FailFast ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/ * IO_MADE_GOOD ; 
 int /*<<< orphan*/  In_sync ; 
 int MD_FAILFAST ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  R1BIO_BehindIO ; 
 int /*<<< orphan*/  R1BIO_MadeGood ; 
 int /*<<< orphan*/  R1BIO_Returned ; 
 int /*<<< orphan*/  R1BIO_Uptodate ; 
 int /*<<< orphan*/  R1BIO_WriteError ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int /*<<< orphan*/  WBCollisionCheck ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  WriteErrorSeen ; 
 int /*<<< orphan*/  WriteMostly ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_end_sector (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  call_bio_endio (struct r1bio*) ; 
 int find_bio_disk (struct r1bio*,struct bio*) ; 
 scalar_t__ is_badblock (struct md_rdev*,scalar_t__,scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  md_error (TYPE_4__*,struct md_rdev*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  r1_bio_write_done (struct r1bio*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,TYPE_3__*) ; 
 int /*<<< orphan*/  remove_wb (struct md_rdev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid1_end_write_request(struct bio *bio)
{
	struct r1bio *r1_bio = bio->bi_private;
	int behind = test_bit(R1BIO_BehindIO, &r1_bio->state);
	struct r1conf *conf = r1_bio->mddev->private;
	struct bio *to_put = NULL;
	int mirror = find_bio_disk(r1_bio, bio);
	struct md_rdev *rdev = conf->mirrors[mirror].rdev;
	bool discard_error;

	discard_error = bio->bi_status && bio_op(bio) == REQ_OP_DISCARD;

	/*
	 * 'one mirror IO has finished' event handler:
	 */
	if (bio->bi_status && !discard_error) {
		set_bit(WriteErrorSeen,	&rdev->flags);
		if (!test_and_set_bit(WantReplacement, &rdev->flags))
			set_bit(MD_RECOVERY_NEEDED, &
				conf->mddev->recovery);

		if (test_bit(FailFast, &rdev->flags) &&
		    (bio->bi_opf & MD_FAILFAST) &&
		    /* We never try FailFast to WriteMostly devices */
		    !test_bit(WriteMostly, &rdev->flags)) {
			md_error(r1_bio->mddev, rdev);
		}

		/*
		 * When the device is faulty, it is not necessary to
		 * handle write error.
		 * For failfast, this is the only remaining device,
		 * We need to retry the write without FailFast.
		 */
		if (!test_bit(Faulty, &rdev->flags))
			set_bit(R1BIO_WriteError, &r1_bio->state);
		else {
			/* Finished with this branch */
			r1_bio->bios[mirror] = NULL;
			to_put = bio;
		}
	} else {
		/*
		 * Set R1BIO_Uptodate in our master bio, so that we
		 * will return a good error code for to the higher
		 * levels even if IO on some other mirrored buffer
		 * fails.
		 *
		 * The 'master' represents the composite IO operation
		 * to user-side. So if something waits for IO, then it
		 * will wait for the 'master' bio.
		 */
		sector_t first_bad;
		int bad_sectors;

		r1_bio->bios[mirror] = NULL;
		to_put = bio;
		/*
		 * Do not set R1BIO_Uptodate if the current device is
		 * rebuilding or Faulty. This is because we cannot use
		 * such device for properly reading the data back (we could
		 * potentially use it, if the current write would have felt
		 * before rdev->recovery_offset, but for simplicity we don't
		 * check this here.
		 */
		if (test_bit(In_sync, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags))
			set_bit(R1BIO_Uptodate, &r1_bio->state);

		/* Maybe we can clear some bad blocks. */
		if (is_badblock(rdev, r1_bio->sector, r1_bio->sectors,
				&first_bad, &bad_sectors) && !discard_error) {
			r1_bio->bios[mirror] = IO_MADE_GOOD;
			set_bit(R1BIO_MadeGood, &r1_bio->state);
		}
	}

	if (behind) {
		if (test_bit(WBCollisionCheck, &rdev->flags)) {
			sector_t lo = r1_bio->sector;
			sector_t hi = r1_bio->sector + r1_bio->sectors;

			remove_wb(rdev, lo, hi);
		}
		if (test_bit(WriteMostly, &rdev->flags))
			atomic_dec(&r1_bio->behind_remaining);

		/*
		 * In behind mode, we ACK the master bio once the I/O
		 * has safely reached all non-writemostly
		 * disks. Setting the Returned bit ensures that this
		 * gets done only once -- we don't ever want to return
		 * -EIO here, instead we'll wait
		 */
		if (atomic_read(&r1_bio->behind_remaining) >= (atomic_read(&r1_bio->remaining)-1) &&
		    test_bit(R1BIO_Uptodate, &r1_bio->state)) {
			/* Maybe we can return now */
			if (!test_and_set_bit(R1BIO_Returned, &r1_bio->state)) {
				struct bio *mbio = r1_bio->master_bio;
				pr_debug("raid1: behind end write sectors"
					 " %llu-%llu\n",
					 (unsigned long long) mbio->bi_iter.bi_sector,
					 (unsigned long long) bio_end_sector(mbio) - 1);
				call_bio_endio(r1_bio);
			}
		}
	}
	if (r1_bio->bios[mirror] == NULL)
		rdev_dec_pending(rdev, conf->mddev);

	/*
	 * Let's see if all mirrored write operations have finished
	 * already.
	 */
	r1_bio_write_done(r1_bio);

	if (to_put)
		bio_put(to_put);
}