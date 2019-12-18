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
struct r10conf {int /*<<< orphan*/  bio_split; TYPE_1__* mirrors; } ;
struct r10bio {int read_slot; int sectors; scalar_t__ sector; int /*<<< orphan*/  state; TYPE_3__* devs; struct bio* master_bio; } ;
struct mddev {scalar_t__ gendisk; int /*<<< orphan*/  bio_set; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; } ;
struct TYPE_6__ {scalar_t__ bi_sector; } ;
struct bio {unsigned long bi_opf; TYPE_4__* bi_disk; struct r10bio* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_2__ bi_iter; } ;
typedef  int gfp_t ;
struct TYPE_8__ {int /*<<< orphan*/  queue; } ;
struct TYPE_7__ {int devnum; scalar_t__ addr; struct md_rdev* rdev; struct bio* bio; } ;
struct TYPE_5__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  FailFast ; 
 int GFP_NOIO ; 
 unsigned long MD_FAILFAST ; 
 int /*<<< orphan*/  R10BIO_FailFast ; 
 unsigned long REQ_SYNC ; 
 int __GFP_HIGH ; 
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 struct bio* bio_clone_fast (struct bio*,int,int /*<<< orphan*/ *) ; 
 int bio_op (struct bio*) ; 
 int bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int const,unsigned long const) ; 
 struct bio* bio_split (struct bio*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ choose_data_offset (struct r10bio*,struct md_rdev*) ; 
 int /*<<< orphan*/  disk_devt (scalar_t__) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_crit_ratelimited (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  raid10_end_read_request ; 
 int /*<<< orphan*/  raid_end_bio_io (struct r10bio*) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct md_rdev* read_balance (struct r10conf*,struct r10bio*,int*) ; 
 int /*<<< orphan*/  regular_request_wait (struct mddev*,struct r10conf*,struct bio*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_bio_remap (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wait_barrier (struct r10conf*) ; 

__attribute__((used)) static void raid10_read_request(struct mddev *mddev, struct bio *bio,
				struct r10bio *r10_bio)
{
	struct r10conf *conf = mddev->private;
	struct bio *read_bio;
	const int op = bio_op(bio);
	const unsigned long do_sync = (bio->bi_opf & REQ_SYNC);
	int max_sectors;
	struct md_rdev *rdev;
	char b[BDEVNAME_SIZE];
	int slot = r10_bio->read_slot;
	struct md_rdev *err_rdev = NULL;
	gfp_t gfp = GFP_NOIO;

	if (r10_bio->devs[slot].rdev) {
		/*
		 * This is an error retry, but we cannot
		 * safely dereference the rdev in the r10_bio,
		 * we must use the one in conf.
		 * If it has already been disconnected (unlikely)
		 * we lose the device name in error messages.
		 */
		int disk;
		/*
		 * As we are blocking raid10, it is a little safer to
		 * use __GFP_HIGH.
		 */
		gfp = GFP_NOIO | __GFP_HIGH;

		rcu_read_lock();
		disk = r10_bio->devs[slot].devnum;
		err_rdev = rcu_dereference(conf->mirrors[disk].rdev);
		if (err_rdev)
			bdevname(err_rdev->bdev, b);
		else {
			strcpy(b, "???");
			/* This never gets dereferenced */
			err_rdev = r10_bio->devs[slot].rdev;
		}
		rcu_read_unlock();
	}

	regular_request_wait(mddev, conf, bio, r10_bio->sectors);
	rdev = read_balance(conf, r10_bio, &max_sectors);
	if (!rdev) {
		if (err_rdev) {
			pr_crit_ratelimited("md/raid10:%s: %s: unrecoverable I/O read error for block %llu\n",
					    mdname(mddev), b,
					    (unsigned long long)r10_bio->sector);
		}
		raid_end_bio_io(r10_bio);
		return;
	}
	if (err_rdev)
		pr_err_ratelimited("md/raid10:%s: %s: redirecting sector %llu to another mirror\n",
				   mdname(mddev),
				   bdevname(rdev->bdev, b),
				   (unsigned long long)r10_bio->sector);
	if (max_sectors < bio_sectors(bio)) {
		struct bio *split = bio_split(bio, max_sectors,
					      gfp, &conf->bio_split);
		bio_chain(split, bio);
		allow_barrier(conf);
		generic_make_request(bio);
		wait_barrier(conf);
		bio = split;
		r10_bio->master_bio = bio;
		r10_bio->sectors = max_sectors;
	}
	slot = r10_bio->read_slot;

	read_bio = bio_clone_fast(bio, gfp, &mddev->bio_set);

	r10_bio->devs[slot].bio = read_bio;
	r10_bio->devs[slot].rdev = rdev;

	read_bio->bi_iter.bi_sector = r10_bio->devs[slot].addr +
		choose_data_offset(r10_bio, rdev);
	bio_set_dev(read_bio, rdev->bdev);
	read_bio->bi_end_io = raid10_end_read_request;
	bio_set_op_attrs(read_bio, op, do_sync);
	if (test_bit(FailFast, &rdev->flags) &&
	    test_bit(R10BIO_FailFast, &r10_bio->state))
	        read_bio->bi_opf |= MD_FAILFAST;
	read_bio->bi_private = r10_bio;

	if (mddev->gendisk)
	        trace_block_bio_remap(read_bio->bi_disk->queue,
	                              read_bio, disk_devt(mddev->gendisk),
	                              r10_bio->sector);
	generic_make_request(read_bio);
	return;
}