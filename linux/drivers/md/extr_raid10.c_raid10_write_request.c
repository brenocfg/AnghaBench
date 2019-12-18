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
struct r10conf {scalar_t__ reshape_safe; scalar_t__ reshape_progress; scalar_t__ pending_count; int copies; int /*<<< orphan*/  bio_split; int /*<<< orphan*/  mddev; TYPE_1__* mirrors; int /*<<< orphan*/  wait_barrier; } ;
struct r10bio {scalar_t__ sectors; int read_slot; TYPE_3__* devs; int /*<<< orphan*/  sector; int /*<<< orphan*/  remaining; struct bio* master_bio; int /*<<< orphan*/  state; } ;
struct mddev {scalar_t__ reshape_position; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  thread; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_wait; scalar_t__ reshape_backwards; int /*<<< orphan*/  recovery; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  raid_disk; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_8__ {scalar_t__ (* area_resyncing ) (struct mddev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int devnum; scalar_t__ addr; struct bio* repl_bio; struct bio* bio; } ;
struct TYPE_5__ {struct md_rdev* rdev; struct md_rdev* replacement; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Blocked ; 
 int /*<<< orphan*/  BlockedBadBlocks ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  MD_RECOVERY_RESHAPE ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 int /*<<< orphan*/  R10BIO_Degraded ; 
 int /*<<< orphan*/  TASK_IDLE ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  WriteErrorSeen ; 
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_end_sector (struct bio*) ; 
 int bio_sectors (struct bio*) ; 
 struct bio* bio_split (struct bio*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int is_badblock (struct md_rdev*,scalar_t__,int,scalar_t__*,int*) ; 
 scalar_t__ max_queued_requests ; 
 int /*<<< orphan*/  md_bitmap_startwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* md_cluster_ops ; 
 int /*<<< orphan*/  md_wait_for_blocked_rdev (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ mddev_is_clustered (struct mddev*) ; 
 int /*<<< orphan*/  one_write_done (struct r10bio*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid10_find_phys (struct r10conf*,struct r10bio*) ; 
 int /*<<< orphan*/  raid10_log (struct mddev*,char*,...) ; 
 int /*<<< orphan*/  raid10_write_one_disk (struct mddev*,struct r10bio*,struct bio*,int,int) ; 
 struct md_rdev* rcu_dereference (struct md_rdev*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  regular_request_wait (struct mddev*,struct r10conf*,struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ stub1 (struct mddev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct mddev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct md_rdev* test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (struct md_rdev*) ; 
 int /*<<< orphan*/  w ; 
 int /*<<< orphan*/  wait_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void raid10_write_request(struct mddev *mddev, struct bio *bio,
				 struct r10bio *r10_bio)
{
	struct r10conf *conf = mddev->private;
	int i;
	struct md_rdev *blocked_rdev;
	sector_t sectors;
	int max_sectors;

	if ((mddev_is_clustered(mddev) &&
	     md_cluster_ops->area_resyncing(mddev, WRITE,
					    bio->bi_iter.bi_sector,
					    bio_end_sector(bio)))) {
		DEFINE_WAIT(w);
		for (;;) {
			prepare_to_wait(&conf->wait_barrier,
					&w, TASK_IDLE);
			if (!md_cluster_ops->area_resyncing(mddev, WRITE,
				 bio->bi_iter.bi_sector, bio_end_sector(bio)))
				break;
			schedule();
		}
		finish_wait(&conf->wait_barrier, &w);
	}

	sectors = r10_bio->sectors;
	regular_request_wait(mddev, conf, bio, sectors);
	if (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
	    (mddev->reshape_backwards
	     ? (bio->bi_iter.bi_sector < conf->reshape_safe &&
		bio->bi_iter.bi_sector + sectors > conf->reshape_progress)
	     : (bio->bi_iter.bi_sector + sectors > conf->reshape_safe &&
		bio->bi_iter.bi_sector < conf->reshape_progress))) {
		/* Need to update reshape_position in metadata */
		mddev->reshape_position = conf->reshape_progress;
		set_mask_bits(&mddev->sb_flags, 0,
			      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
		md_wakeup_thread(mddev->thread);
		raid10_log(conf->mddev, "wait reshape metadata");
		wait_event(mddev->sb_wait,
			   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags));

		conf->reshape_safe = mddev->reshape_position;
	}

	if (conf->pending_count >= max_queued_requests) {
		md_wakeup_thread(mddev->thread);
		raid10_log(mddev, "wait queued");
		wait_event(conf->wait_barrier,
			   conf->pending_count < max_queued_requests);
	}
	/* first select target devices under rcu_lock and
	 * inc refcount on their rdev.  Record them by setting
	 * bios[x] to bio
	 * If there are known/acknowledged bad blocks on any device
	 * on which we have seen a write error, we want to avoid
	 * writing to those blocks.  This potentially requires several
	 * writes to write around the bad blocks.  Each set of writes
	 * gets its own r10_bio with a set of bios attached.
	 */

	r10_bio->read_slot = -1; /* make sure repl_bio gets freed */
	raid10_find_phys(conf, r10_bio);
retry_write:
	blocked_rdev = NULL;
	rcu_read_lock();
	max_sectors = r10_bio->sectors;

	for (i = 0;  i < conf->copies; i++) {
		int d = r10_bio->devs[i].devnum;
		struct md_rdev *rdev = rcu_dereference(conf->mirrors[d].rdev);
		struct md_rdev *rrdev = rcu_dereference(
			conf->mirrors[d].replacement);
		if (rdev == rrdev)
			rrdev = NULL;
		if (rdev && unlikely(test_bit(Blocked, &rdev->flags))) {
			atomic_inc(&rdev->nr_pending);
			blocked_rdev = rdev;
			break;
		}
		if (rrdev && unlikely(test_bit(Blocked, &rrdev->flags))) {
			atomic_inc(&rrdev->nr_pending);
			blocked_rdev = rrdev;
			break;
		}
		if (rdev && (test_bit(Faulty, &rdev->flags)))
			rdev = NULL;
		if (rrdev && (test_bit(Faulty, &rrdev->flags)))
			rrdev = NULL;

		r10_bio->devs[i].bio = NULL;
		r10_bio->devs[i].repl_bio = NULL;

		if (!rdev && !rrdev) {
			set_bit(R10BIO_Degraded, &r10_bio->state);
			continue;
		}
		if (rdev && test_bit(WriteErrorSeen, &rdev->flags)) {
			sector_t first_bad;
			sector_t dev_sector = r10_bio->devs[i].addr;
			int bad_sectors;
			int is_bad;

			is_bad = is_badblock(rdev, dev_sector, max_sectors,
					     &first_bad, &bad_sectors);
			if (is_bad < 0) {
				/* Mustn't write here until the bad block
				 * is acknowledged
				 */
				atomic_inc(&rdev->nr_pending);
				set_bit(BlockedBadBlocks, &rdev->flags);
				blocked_rdev = rdev;
				break;
			}
			if (is_bad && first_bad <= dev_sector) {
				/* Cannot write here at all */
				bad_sectors -= (dev_sector - first_bad);
				if (bad_sectors < max_sectors)
					/* Mustn't write more than bad_sectors
					 * to other devices yet
					 */
					max_sectors = bad_sectors;
				/* We don't set R10BIO_Degraded as that
				 * only applies if the disk is missing,
				 * so it might be re-added, and we want to
				 * know to recover this chunk.
				 * In this case the device is here, and the
				 * fact that this chunk is not in-sync is
				 * recorded in the bad block log.
				 */
				continue;
			}
			if (is_bad) {
				int good_sectors = first_bad - dev_sector;
				if (good_sectors < max_sectors)
					max_sectors = good_sectors;
			}
		}
		if (rdev) {
			r10_bio->devs[i].bio = bio;
			atomic_inc(&rdev->nr_pending);
		}
		if (rrdev) {
			r10_bio->devs[i].repl_bio = bio;
			atomic_inc(&rrdev->nr_pending);
		}
	}
	rcu_read_unlock();

	if (unlikely(blocked_rdev)) {
		/* Have to wait for this device to get unblocked, then retry */
		int j;
		int d;

		for (j = 0; j < i; j++) {
			if (r10_bio->devs[j].bio) {
				d = r10_bio->devs[j].devnum;
				rdev_dec_pending(conf->mirrors[d].rdev, mddev);
			}
			if (r10_bio->devs[j].repl_bio) {
				struct md_rdev *rdev;
				d = r10_bio->devs[j].devnum;
				rdev = conf->mirrors[d].replacement;
				if (!rdev) {
					/* Race with remove_disk */
					smp_mb();
					rdev = conf->mirrors[d].rdev;
				}
				rdev_dec_pending(rdev, mddev);
			}
		}
		allow_barrier(conf);
		raid10_log(conf->mddev, "wait rdev %d blocked", blocked_rdev->raid_disk);
		md_wait_for_blocked_rdev(blocked_rdev, mddev);
		wait_barrier(conf);
		goto retry_write;
	}

	if (max_sectors < r10_bio->sectors)
		r10_bio->sectors = max_sectors;

	if (r10_bio->sectors < bio_sectors(bio)) {
		struct bio *split = bio_split(bio, r10_bio->sectors,
					      GFP_NOIO, &conf->bio_split);
		bio_chain(split, bio);
		allow_barrier(conf);
		generic_make_request(bio);
		wait_barrier(conf);
		bio = split;
		r10_bio->master_bio = bio;
	}

	atomic_set(&r10_bio->remaining, 1);
	md_bitmap_startwrite(mddev->bitmap, r10_bio->sector, r10_bio->sectors, 0);

	for (i = 0; i < conf->copies; i++) {
		if (r10_bio->devs[i].bio)
			raid10_write_one_disk(mddev, r10_bio, bio, false, i);
		if (r10_bio->devs[i].repl_bio)
			raid10_write_one_disk(mddev, r10_bio, bio, true, i);
	}
	one_write_done(r10_bio);
}