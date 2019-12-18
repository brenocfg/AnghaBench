#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int chunk_mask; } ;
struct r10conf {void* reshape_progress; int reshape_safe; int offset_diff; int cluster_sync_high; int cluster_sync_low; int copies; TYPE_1__* mirrors; TYPE_5__ geo; int /*<<< orphan*/  r10buf_pool; scalar_t__ reshape_checkpoint; TYPE_5__ prev; } ;
struct r10bio {scalar_t__ state; int sector; int sectors; size_t read_slot; int /*<<< orphan*/  remaining; TYPE_3__* devs; struct bio* master_bio; struct mddev* mddev; } ;
struct page {int dummy; } ;
struct mdp_superblock_1 {int /*<<< orphan*/  reshape_position; } ;
struct mddev {int curr_resync_completed; int reshape_position; scalar_t__ sb_flags; scalar_t__ recovery; scalar_t__ reshape_backwards; int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  thread; int /*<<< orphan*/  kobj; struct r10conf* private; } ;
struct md_rdev {scalar_t__ flags; scalar_t__ new_data_offset; int /*<<< orphan*/  bdev; int /*<<< orphan*/  sb_page; scalar_t__ data_offset; } ;
struct TYPE_10__ {scalar_t__ bi_sector; scalar_t__ bi_size; } ;
struct bio {unsigned long bi_flags; struct bio* bi_next; int /*<<< orphan*/  bi_end_io; TYPE_2__ bi_iter; scalar_t__ bi_vcnt; scalar_t__ bi_status; struct r10bio* bi_private; } ;
typedef  int sector_t ;
struct TYPE_14__ {struct page** pages; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* resync_info_update ) (struct mddev*,int,int) ;} ;
struct TYPE_11__ {size_t devnum; struct bio* bio; scalar_t__ addr; struct bio* repl_bio; } ;
struct TYPE_9__ {int /*<<< orphan*/  rdev; int /*<<< orphan*/  replacement; } ;

/* Variables and functions */
 unsigned long BIO_RESET_BITS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CLUSTER_RESYNC_WINDOW_SECTORS ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  R10BIO_IsReshape ; 
 int /*<<< orphan*/  R10BIO_Previous ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int RESYNC_BLOCK_SIZE ; 
 int /*<<< orphan*/  RESYNC_PAGES ; 
 int /*<<< orphan*/  __raid10_find_phys (TYPE_5__*,struct r10bio*) ; 
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc_mddev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mddev*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_reshape_read ; 
 int /*<<< orphan*/  end_reshape_write ; 
 int first_dev_address (int,TYPE_5__*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 TYPE_6__* get_resync_pages (struct bio*) ; 
 scalar_t__ jiffies ; 
 int last_dev_address (int,TYPE_5__*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_barrier (struct r10conf*) ; 
 TYPE_4__* md_cluster_ops ; 
 int /*<<< orphan*/  md_sync_acct_bio (struct bio*,int) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ mddev_is_clustered (struct mddev*) ; 
 int /*<<< orphan*/  mempool_free (struct r10bio*,int /*<<< orphan*/ *) ; 
 struct mdp_superblock_1* page_address (int /*<<< orphan*/ ) ; 
 struct r10bio* raid10_alloc_init_r10buf (struct r10conf*) ; 
 void* raid10_size (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise_barrier (struct r10conf*,int) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct md_rdev* read_balance (struct r10conf*,struct r10bio*,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int,int) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wait_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static sector_t reshape_request(struct mddev *mddev, sector_t sector_nr,
				int *skipped)
{
	/* We simply copy at most one chunk (smallest of old and new)
	 * at a time, possibly less if that exceeds RESYNC_PAGES,
	 * or we hit a bad block or something.
	 * This might mean we pause for normal IO in the middle of
	 * a chunk, but that is not a problem as mddev->reshape_position
	 * can record any location.
	 *
	 * If we will want to write to a location that isn't
	 * yet recorded as 'safe' (i.e. in metadata on disk) then
	 * we need to flush all reshape requests and update the metadata.
	 *
	 * When reshaping forwards (e.g. to more devices), we interpret
	 * 'safe' as the earliest block which might not have been copied
	 * down yet.  We divide this by previous stripe size and multiply
	 * by previous stripe length to get lowest device offset that we
	 * cannot write to yet.
	 * We interpret 'sector_nr' as an address that we want to write to.
	 * From this we use last_device_address() to find where we might
	 * write to, and first_device_address on the  'safe' position.
	 * If this 'next' write position is after the 'safe' position,
	 * we must update the metadata to increase the 'safe' position.
	 *
	 * When reshaping backwards, we round in the opposite direction
	 * and perform the reverse test:  next write position must not be
	 * less than current safe position.
	 *
	 * In all this the minimum difference in data offsets
	 * (conf->offset_diff - always positive) allows a bit of slack,
	 * so next can be after 'safe', but not by more than offset_diff
	 *
	 * We need to prepare all the bios here before we start any IO
	 * to ensure the size we choose is acceptable to all devices.
	 * The means one for each copy for write-out and an extra one for
	 * read-in.
	 * We store the read-in bio in ->master_bio and the others in
	 * ->devs[x].bio and ->devs[x].repl_bio.
	 */
	struct r10conf *conf = mddev->private;
	struct r10bio *r10_bio;
	sector_t next, safe, last;
	int max_sectors;
	int nr_sectors;
	int s;
	struct md_rdev *rdev;
	int need_flush = 0;
	struct bio *blist;
	struct bio *bio, *read_bio;
	int sectors_done = 0;
	struct page **pages;

	if (sector_nr == 0) {
		/* If restarting in the middle, skip the initial sectors */
		if (mddev->reshape_backwards &&
		    conf->reshape_progress < raid10_size(mddev, 0, 0)) {
			sector_nr = (raid10_size(mddev, 0, 0)
				     - conf->reshape_progress);
		} else if (!mddev->reshape_backwards &&
			   conf->reshape_progress > 0)
			sector_nr = conf->reshape_progress;
		if (sector_nr) {
			mddev->curr_resync_completed = sector_nr;
			sysfs_notify(&mddev->kobj, NULL, "sync_completed");
			*skipped = 1;
			return sector_nr;
		}
	}

	/* We don't use sector_nr to track where we are up to
	 * as that doesn't work well for ->reshape_backwards.
	 * So just use ->reshape_progress.
	 */
	if (mddev->reshape_backwards) {
		/* 'next' is the earliest device address that we might
		 * write to for this chunk in the new layout
		 */
		next = first_dev_address(conf->reshape_progress - 1,
					 &conf->geo);

		/* 'safe' is the last device address that we might read from
		 * in the old layout after a restart
		 */
		safe = last_dev_address(conf->reshape_safe - 1,
					&conf->prev);

		if (next + conf->offset_diff < safe)
			need_flush = 1;

		last = conf->reshape_progress - 1;
		sector_nr = last & ~(sector_t)(conf->geo.chunk_mask
					       & conf->prev.chunk_mask);
		if (sector_nr + RESYNC_BLOCK_SIZE/512 < last)
			sector_nr = last + 1 - RESYNC_BLOCK_SIZE/512;
	} else {
		/* 'next' is after the last device address that we
		 * might write to for this chunk in the new layout
		 */
		next = last_dev_address(conf->reshape_progress, &conf->geo);

		/* 'safe' is the earliest device address that we might
		 * read from in the old layout after a restart
		 */
		safe = first_dev_address(conf->reshape_safe, &conf->prev);

		/* Need to update metadata if 'next' might be beyond 'safe'
		 * as that would possibly corrupt data
		 */
		if (next > safe + conf->offset_diff)
			need_flush = 1;

		sector_nr = conf->reshape_progress;
		last  = sector_nr | (conf->geo.chunk_mask
				     & conf->prev.chunk_mask);

		if (sector_nr + RESYNC_BLOCK_SIZE/512 <= last)
			last = sector_nr + RESYNC_BLOCK_SIZE/512 - 1;
	}

	if (need_flush ||
	    time_after(jiffies, conf->reshape_checkpoint + 10*HZ)) {
		/* Need to update reshape_position in metadata */
		wait_barrier(conf);
		mddev->reshape_position = conf->reshape_progress;
		if (mddev->reshape_backwards)
			mddev->curr_resync_completed = raid10_size(mddev, 0, 0)
				- conf->reshape_progress;
		else
			mddev->curr_resync_completed = conf->reshape_progress;
		conf->reshape_checkpoint = jiffies;
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		md_wakeup_thread(mddev->thread);
		wait_event(mddev->sb_wait, mddev->sb_flags == 0 ||
			   test_bit(MD_RECOVERY_INTR, &mddev->recovery));
		if (test_bit(MD_RECOVERY_INTR, &mddev->recovery)) {
			allow_barrier(conf);
			return sectors_done;
		}
		conf->reshape_safe = mddev->reshape_position;
		allow_barrier(conf);
	}

	raise_barrier(conf, 0);
read_more:
	/* Now schedule reads for blocks from sector_nr to last */
	r10_bio = raid10_alloc_init_r10buf(conf);
	r10_bio->state = 0;
	raise_barrier(conf, 1);
	atomic_set(&r10_bio->remaining, 0);
	r10_bio->mddev = mddev;
	r10_bio->sector = sector_nr;
	set_bit(R10BIO_IsReshape, &r10_bio->state);
	r10_bio->sectors = last - sector_nr + 1;
	rdev = read_balance(conf, r10_bio, &max_sectors);
	BUG_ON(!test_bit(R10BIO_Previous, &r10_bio->state));

	if (!rdev) {
		/* Cannot read from here, so need to record bad blocks
		 * on all the target devices.
		 */
		// FIXME
		mempool_free(r10_bio, &conf->r10buf_pool);
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		return sectors_done;
	}

	read_bio = bio_alloc_mddev(GFP_KERNEL, RESYNC_PAGES, mddev);

	bio_set_dev(read_bio, rdev->bdev);
	read_bio->bi_iter.bi_sector = (r10_bio->devs[r10_bio->read_slot].addr
			       + rdev->data_offset);
	read_bio->bi_private = r10_bio;
	read_bio->bi_end_io = end_reshape_read;
	bio_set_op_attrs(read_bio, REQ_OP_READ, 0);
	read_bio->bi_flags &= (~0UL << BIO_RESET_BITS);
	read_bio->bi_status = 0;
	read_bio->bi_vcnt = 0;
	read_bio->bi_iter.bi_size = 0;
	r10_bio->master_bio = read_bio;
	r10_bio->read_slot = r10_bio->devs[r10_bio->read_slot].devnum;

	/*
	 * Broadcast RESYNC message to other nodes, so all nodes would not
	 * write to the region to avoid conflict.
	*/
	if (mddev_is_clustered(mddev) && conf->cluster_sync_high <= sector_nr) {
		struct mdp_superblock_1 *sb = NULL;
		int sb_reshape_pos = 0;

		conf->cluster_sync_low = sector_nr;
		conf->cluster_sync_high = sector_nr + CLUSTER_RESYNC_WINDOW_SECTORS;
		sb = page_address(rdev->sb_page);
		if (sb) {
			sb_reshape_pos = le64_to_cpu(sb->reshape_position);
			/*
			 * Set cluster_sync_low again if next address for array
			 * reshape is less than cluster_sync_low. Since we can't
			 * update cluster_sync_low until it has finished reshape.
			 */
			if (sb_reshape_pos < conf->cluster_sync_low)
				conf->cluster_sync_low = sb_reshape_pos;
		}

		md_cluster_ops->resync_info_update(mddev, conf->cluster_sync_low,
							  conf->cluster_sync_high);
	}

	/* Now find the locations in the new layout */
	__raid10_find_phys(&conf->geo, r10_bio);

	blist = read_bio;
	read_bio->bi_next = NULL;

	rcu_read_lock();
	for (s = 0; s < conf->copies*2; s++) {
		struct bio *b;
		int d = r10_bio->devs[s/2].devnum;
		struct md_rdev *rdev2;
		if (s&1) {
			rdev2 = rcu_dereference(conf->mirrors[d].replacement);
			b = r10_bio->devs[s/2].repl_bio;
		} else {
			rdev2 = rcu_dereference(conf->mirrors[d].rdev);
			b = r10_bio->devs[s/2].bio;
		}
		if (!rdev2 || test_bit(Faulty, &rdev2->flags))
			continue;

		bio_set_dev(b, rdev2->bdev);
		b->bi_iter.bi_sector = r10_bio->devs[s/2].addr +
			rdev2->new_data_offset;
		b->bi_end_io = end_reshape_write;
		bio_set_op_attrs(b, REQ_OP_WRITE, 0);
		b->bi_next = blist;
		blist = b;
	}

	/* Now add as many pages as possible to all of these bios. */

	nr_sectors = 0;
	pages = get_resync_pages(r10_bio->devs[0].bio)->pages;
	for (s = 0 ; s < max_sectors; s += PAGE_SIZE >> 9) {
		struct page *page = pages[s / (PAGE_SIZE >> 9)];
		int len = (max_sectors - s) << 9;
		if (len > PAGE_SIZE)
			len = PAGE_SIZE;
		for (bio = blist; bio ; bio = bio->bi_next) {
			/*
			 * won't fail because the vec table is big enough
			 * to hold all these pages
			 */
			bio_add_page(bio, page, len, 0);
		}
		sector_nr += len >> 9;
		nr_sectors += len >> 9;
	}
	rcu_read_unlock();
	r10_bio->sectors = nr_sectors;

	/* Now submit the read */
	md_sync_acct_bio(read_bio, r10_bio->sectors);
	atomic_inc(&r10_bio->remaining);
	read_bio->bi_next = NULL;
	generic_make_request(read_bio);
	sectors_done += nr_sectors;
	if (sector_nr <= last)
		goto read_more;

	lower_barrier(conf);

	/* Now that we have done the whole section we can
	 * update reshape_progress
	 */
	if (mddev->reshape_backwards)
		conf->reshape_progress -= sectors_done;
	else
		conf->reshape_progress += sectors_done;

	return sectors_done;
}