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
struct stripe_head {int /*<<< orphan*/  state; struct stripe_head* batch_head; } ;
struct r5conf {scalar_t__ reshape_progress; int reshape_safe; int /*<<< orphan*/  wait_for_overlap; int /*<<< orphan*/  preread_active_stripes; int /*<<< orphan*/  gen_lock; int /*<<< orphan*/  device_lock; } ;
struct mddev {scalar_t__ degraded; scalar_t__ reshape_position; int /*<<< orphan*/  thread; scalar_t__ reshape_backwards; struct r5conf* private; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_status; int /*<<< orphan*/ * bi_next; TYPE_1__ bi_iter; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ MaxSector ; 
 int const READ ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 int REQ_RAHEAD ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_EXPANDING ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 int /*<<< orphan*/  STRIPE_R5C_PREFLUSH ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int const WRITE ; 
 int /*<<< orphan*/  add_stripe_bio (struct stripe_head*,struct bio*,int,int const,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int bio_data_dir (struct bio*) ; 
 int bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 struct bio* chunk_aligned_read (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int log_handle_flush_request (struct r5conf*,struct bio*) ; 
 int /*<<< orphan*/  make_discard_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  md_flush_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_write_end (struct mddev*) ; 
 int /*<<< orphan*/  md_write_start (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int raid5_compute_sector (struct r5conf*,int,int,int*,int /*<<< orphan*/ *) ; 
 struct stripe_head* raid5_get_active_stripe (struct r5conf*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid5_release_stripe (struct stripe_head*) ; 
 int read_seqcount_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_stripe_plug (struct mddev*,struct stripe_head*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  w ; 

__attribute__((used)) static bool raid5_make_request(struct mddev *mddev, struct bio * bi)
{
	struct r5conf *conf = mddev->private;
	int dd_idx;
	sector_t new_sector;
	sector_t logical_sector, last_sector;
	struct stripe_head *sh;
	const int rw = bio_data_dir(bi);
	DEFINE_WAIT(w);
	bool do_prepare;
	bool do_flush = false;

	if (unlikely(bi->bi_opf & REQ_PREFLUSH)) {
		int ret = log_handle_flush_request(conf, bi);

		if (ret == 0)
			return true;
		if (ret == -ENODEV) {
			md_flush_request(mddev, bi);
			return true;
		}
		/* ret == -EAGAIN, fallback */
		/*
		 * if r5l_handle_flush_request() didn't clear REQ_PREFLUSH,
		 * we need to flush journal device
		 */
		do_flush = bi->bi_opf & REQ_PREFLUSH;
	}

	if (!md_write_start(mddev, bi))
		return false;
	/*
	 * If array is degraded, better not do chunk aligned read because
	 * later we might have to read it again in order to reconstruct
	 * data on failed drives.
	 */
	if (rw == READ && mddev->degraded == 0 &&
	    mddev->reshape_position == MaxSector) {
		bi = chunk_aligned_read(mddev, bi);
		if (!bi)
			return true;
	}

	if (unlikely(bio_op(bi) == REQ_OP_DISCARD)) {
		make_discard_request(mddev, bi);
		md_write_end(mddev);
		return true;
	}

	logical_sector = bi->bi_iter.bi_sector & ~((sector_t)STRIPE_SECTORS-1);
	last_sector = bio_end_sector(bi);
	bi->bi_next = NULL;

	prepare_to_wait(&conf->wait_for_overlap, &w, TASK_UNINTERRUPTIBLE);
	for (;logical_sector < last_sector; logical_sector += STRIPE_SECTORS) {
		int previous;
		int seq;

		do_prepare = false;
	retry:
		seq = read_seqcount_begin(&conf->gen_lock);
		previous = 0;
		if (do_prepare)
			prepare_to_wait(&conf->wait_for_overlap, &w,
				TASK_UNINTERRUPTIBLE);
		if (unlikely(conf->reshape_progress != MaxSector)) {
			/* spinlock is needed as reshape_progress may be
			 * 64bit on a 32bit platform, and so it might be
			 * possible to see a half-updated value
			 * Of course reshape_progress could change after
			 * the lock is dropped, so once we get a reference
			 * to the stripe that we think it is, we will have
			 * to check again.
			 */
			spin_lock_irq(&conf->device_lock);
			if (mddev->reshape_backwards
			    ? logical_sector < conf->reshape_progress
			    : logical_sector >= conf->reshape_progress) {
				previous = 1;
			} else {
				if (mddev->reshape_backwards
				    ? logical_sector < conf->reshape_safe
				    : logical_sector >= conf->reshape_safe) {
					spin_unlock_irq(&conf->device_lock);
					schedule();
					do_prepare = true;
					goto retry;
				}
			}
			spin_unlock_irq(&conf->device_lock);
		}

		new_sector = raid5_compute_sector(conf, logical_sector,
						  previous,
						  &dd_idx, NULL);
		pr_debug("raid456: raid5_make_request, sector %llu logical %llu\n",
			(unsigned long long)new_sector,
			(unsigned long long)logical_sector);

		sh = raid5_get_active_stripe(conf, new_sector, previous,
				       (bi->bi_opf & REQ_RAHEAD), 0);
		if (sh) {
			if (unlikely(previous)) {
				/* expansion might have moved on while waiting for a
				 * stripe, so we must do the range check again.
				 * Expansion could still move past after this
				 * test, but as we are holding a reference to
				 * 'sh', we know that if that happens,
				 *  STRIPE_EXPANDING will get set and the expansion
				 * won't proceed until we finish with the stripe.
				 */
				int must_retry = 0;
				spin_lock_irq(&conf->device_lock);
				if (mddev->reshape_backwards
				    ? logical_sector >= conf->reshape_progress
				    : logical_sector < conf->reshape_progress)
					/* mismatch, need to try again */
					must_retry = 1;
				spin_unlock_irq(&conf->device_lock);
				if (must_retry) {
					raid5_release_stripe(sh);
					schedule();
					do_prepare = true;
					goto retry;
				}
			}
			if (read_seqcount_retry(&conf->gen_lock, seq)) {
				/* Might have got the wrong stripe_head
				 * by accident
				 */
				raid5_release_stripe(sh);
				goto retry;
			}

			if (test_bit(STRIPE_EXPANDING, &sh->state) ||
			    !add_stripe_bio(sh, bi, dd_idx, rw, previous)) {
				/* Stripe is busy expanding or
				 * add failed due to overlap.  Flush everything
				 * and wait a while
				 */
				md_wakeup_thread(mddev->thread);
				raid5_release_stripe(sh);
				schedule();
				do_prepare = true;
				goto retry;
			}
			if (do_flush) {
				set_bit(STRIPE_R5C_PREFLUSH, &sh->state);
				/* we only need flush for one stripe */
				do_flush = false;
			}

			if (!sh->batch_head)
				set_bit(STRIPE_HANDLE, &sh->state);
			clear_bit(STRIPE_DELAYED, &sh->state);
			if ((!sh->batch_head || sh == sh->batch_head) &&
			    (bi->bi_opf & REQ_SYNC) &&
			    !test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
				atomic_inc(&conf->preread_active_stripes);
			release_stripe_plug(mddev, sh);
		} else {
			/* cannot get stripe for read-ahead, just give-up */
			bi->bi_status = BLK_STS_IOERR;
			break;
		}
	}
	finish_wait(&conf->wait_for_overlap, &w);

	if (rw == WRITE)
		md_write_end(mddev);
	bio_endio(bi);
	return true;
}