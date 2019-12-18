#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stripe_head_state {scalar_t__ failed; scalar_t__ written; scalar_t__ to_write; int /*<<< orphan*/  to_read; } ;
struct stripe_head {int /*<<< orphan*/  state; TYPE_3__* dev; int /*<<< orphan*/  sector; int /*<<< orphan*/  stripe_lock; scalar_t__ overwrite_disks; int /*<<< orphan*/  batch_head; } ;
struct r5conf {scalar_t__ max_degraded; TYPE_4__* mddev; int /*<<< orphan*/  pending_full_writes; int /*<<< orphan*/  wait_for_overlap; TYPE_1__* disks; } ;
struct md_rdev {int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
struct TYPE_10__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  bitmap; } ;
struct TYPE_9__ {scalar_t__ sector; int /*<<< orphan*/  flags; struct bio* toread; int /*<<< orphan*/  orig_page; int /*<<< orphan*/  page; struct bio* written; struct bio* towrite; } ;
struct TYPE_7__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  R5_Insync ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_Overlap ; 
 int /*<<< orphan*/  R5_ReadError ; 
 int /*<<< orphan*/  R5_SkipCopy ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  R5_Wantfill ; 
 int /*<<< orphan*/  STRIPE_FULL_WRITE ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_stripe_write_finished (struct stripe_head*) ; 
 int /*<<< orphan*/  md_bitmap_endwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_error (TYPE_4__*,struct md_rdev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_write_end (TYPE_4__*) ; 
 struct bio* r5_next_bio (struct bio*,scalar_t__) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,TYPE_4__*) ; 
 int /*<<< orphan*/  rdev_set_badblocks (struct md_rdev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_failed_stripe(struct r5conf *conf, struct stripe_head *sh,
		     struct stripe_head_state *s, int disks)
{
	int i;
	BUG_ON(sh->batch_head);
	for (i = disks; i--; ) {
		struct bio *bi;
		int bitmap_end = 0;

		if (test_bit(R5_ReadError, &sh->dev[i].flags)) {
			struct md_rdev *rdev;
			rcu_read_lock();
			rdev = rcu_dereference(conf->disks[i].rdev);
			if (rdev && test_bit(In_sync, &rdev->flags) &&
			    !test_bit(Faulty, &rdev->flags))
				atomic_inc(&rdev->nr_pending);
			else
				rdev = NULL;
			rcu_read_unlock();
			if (rdev) {
				if (!rdev_set_badblocks(
					    rdev,
					    sh->sector,
					    STRIPE_SECTORS, 0))
					md_error(conf->mddev, rdev);
				rdev_dec_pending(rdev, conf->mddev);
			}
		}
		spin_lock_irq(&sh->stripe_lock);
		/* fail all writes first */
		bi = sh->dev[i].towrite;
		sh->dev[i].towrite = NULL;
		sh->overwrite_disks = 0;
		spin_unlock_irq(&sh->stripe_lock);
		if (bi)
			bitmap_end = 1;

		log_stripe_write_finished(sh);

		if (test_and_clear_bit(R5_Overlap, &sh->dev[i].flags))
			wake_up(&conf->wait_for_overlap);

		while (bi && bi->bi_iter.bi_sector <
			sh->dev[i].sector + STRIPE_SECTORS) {
			struct bio *nextbi = r5_next_bio(bi, sh->dev[i].sector);

			md_write_end(conf->mddev);
			bio_io_error(bi);
			bi = nextbi;
		}
		if (bitmap_end)
			md_bitmap_endwrite(conf->mddev->bitmap, sh->sector,
					   STRIPE_SECTORS, 0, 0);
		bitmap_end = 0;
		/* and fail all 'written' */
		bi = sh->dev[i].written;
		sh->dev[i].written = NULL;
		if (test_and_clear_bit(R5_SkipCopy, &sh->dev[i].flags)) {
			WARN_ON(test_bit(R5_UPTODATE, &sh->dev[i].flags));
			sh->dev[i].page = sh->dev[i].orig_page;
		}

		if (bi) bitmap_end = 1;
		while (bi && bi->bi_iter.bi_sector <
		       sh->dev[i].sector + STRIPE_SECTORS) {
			struct bio *bi2 = r5_next_bio(bi, sh->dev[i].sector);

			md_write_end(conf->mddev);
			bio_io_error(bi);
			bi = bi2;
		}

		/* fail any reads if this device is non-operational and
		 * the data has not reached the cache yet.
		 */
		if (!test_bit(R5_Wantfill, &sh->dev[i].flags) &&
		    s->failed > conf->max_degraded &&
		    (!test_bit(R5_Insync, &sh->dev[i].flags) ||
		      test_bit(R5_ReadError, &sh->dev[i].flags))) {
			spin_lock_irq(&sh->stripe_lock);
			bi = sh->dev[i].toread;
			sh->dev[i].toread = NULL;
			spin_unlock_irq(&sh->stripe_lock);
			if (test_and_clear_bit(R5_Overlap, &sh->dev[i].flags))
				wake_up(&conf->wait_for_overlap);
			if (bi)
				s->to_read--;
			while (bi && bi->bi_iter.bi_sector <
			       sh->dev[i].sector + STRIPE_SECTORS) {
				struct bio *nextbi =
					r5_next_bio(bi, sh->dev[i].sector);

				bio_io_error(bi);
				bi = nextbi;
			}
		}
		if (bitmap_end)
			md_bitmap_endwrite(conf->mddev->bitmap, sh->sector,
					   STRIPE_SECTORS, 0, 0);
		/* If we were in the middle of a write the parity block might
		 * still be locked - so just clear all R5_LOCKED flags
		 */
		clear_bit(R5_LOCKED, &sh->dev[i].flags);
	}
	s->to_write = 0;
	s->written = 0;

	if (test_and_clear_bit(STRIPE_FULL_WRITE, &sh->state))
		if (atomic_dec_and_test(&conf->pending_full_writes))
			md_wakeup_thread(conf->mddev->thread);
}