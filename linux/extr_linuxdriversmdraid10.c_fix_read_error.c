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
struct r10conf {int copies; int /*<<< orphan*/  tmppage; TYPE_2__* mirrors; } ;
struct r10bio {int sectors; size_t read_slot; TYPE_1__* devs; } ;
struct mddev {int /*<<< orphan*/  max_corr_read_errors; } ;
struct md_rdev {int /*<<< orphan*/  corrected_errors; int /*<<< orphan*/  bdev; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; int /*<<< orphan*/  read_errors; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {struct md_rdev* rdev; } ;
struct TYPE_3__ {int devnum; scalar_t__ addr; void* bio; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  Faulty ; 
 void* IO_BLOCKED ; 
 int /*<<< orphan*/  In_sync ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 char* bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_decay_read_errors (struct mddev*,struct md_rdev*) ; 
 scalar_t__ choose_data_offset (struct r10bio*,struct md_rdev*) ; 
 scalar_t__ is_badblock (struct md_rdev*,scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,unsigned long long,char*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,...) ; 
 int r10_sync_page_io (struct md_rdev*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct md_rdev* rcu_dereference (struct md_rdev*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  rdev_set_badblocks (struct md_rdev*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int sync_page_io (struct md_rdev*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fix_read_error(struct r10conf *conf, struct mddev *mddev, struct r10bio *r10_bio)
{
	int sect = 0; /* Offset from r10_bio->sector */
	int sectors = r10_bio->sectors;
	struct md_rdev *rdev;
	int max_read_errors = atomic_read(&mddev->max_corr_read_errors);
	int d = r10_bio->devs[r10_bio->read_slot].devnum;

	/* still own a reference to this rdev, so it cannot
	 * have been cleared recently.
	 */
	rdev = conf->mirrors[d].rdev;

	if (test_bit(Faulty, &rdev->flags))
		/* drive has already been failed, just ignore any
		   more fix_read_error() attempts */
		return;

	check_decay_read_errors(mddev, rdev);
	atomic_inc(&rdev->read_errors);
	if (atomic_read(&rdev->read_errors) > max_read_errors) {
		char b[BDEVNAME_SIZE];
		bdevname(rdev->bdev, b);

		pr_notice("md/raid10:%s: %s: Raid device exceeded read_error threshold [cur %d:max %d]\n",
			  mdname(mddev), b,
			  atomic_read(&rdev->read_errors), max_read_errors);
		pr_notice("md/raid10:%s: %s: Failing raid device\n",
			  mdname(mddev), b);
		md_error(mddev, rdev);
		r10_bio->devs[r10_bio->read_slot].bio = IO_BLOCKED;
		return;
	}

	while(sectors) {
		int s = sectors;
		int sl = r10_bio->read_slot;
		int success = 0;
		int start;

		if (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;

		rcu_read_lock();
		do {
			sector_t first_bad;
			int bad_sectors;

			d = r10_bio->devs[sl].devnum;
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			if (rdev &&
			    test_bit(In_sync, &rdev->flags) &&
			    !test_bit(Faulty, &rdev->flags) &&
			    is_badblock(rdev, r10_bio->devs[sl].addr + sect, s,
					&first_bad, &bad_sectors) == 0) {
				atomic_inc(&rdev->nr_pending);
				rcu_read_unlock();
				success = sync_page_io(rdev,
						       r10_bio->devs[sl].addr +
						       sect,
						       s<<9,
						       conf->tmppage,
						       REQ_OP_READ, 0, false);
				rdev_dec_pending(rdev, mddev);
				rcu_read_lock();
				if (success)
					break;
			}
			sl++;
			if (sl == conf->copies)
				sl = 0;
		} while (!success && sl != r10_bio->read_slot);
		rcu_read_unlock();

		if (!success) {
			/* Cannot read from anywhere, just mark the block
			 * as bad on the first device to discourage future
			 * reads.
			 */
			int dn = r10_bio->devs[r10_bio->read_slot].devnum;
			rdev = conf->mirrors[dn].rdev;

			if (!rdev_set_badblocks(
				    rdev,
				    r10_bio->devs[r10_bio->read_slot].addr
				    + sect,
				    s, 0)) {
				md_error(mddev, rdev);
				r10_bio->devs[r10_bio->read_slot].bio
					= IO_BLOCKED;
			}
			break;
		}

		start = sl;
		/* write it back and re-read */
		rcu_read_lock();
		while (sl != r10_bio->read_slot) {
			char b[BDEVNAME_SIZE];

			if (sl==0)
				sl = conf->copies;
			sl--;
			d = r10_bio->devs[sl].devnum;
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			if (!rdev ||
			    test_bit(Faulty, &rdev->flags) ||
			    !test_bit(In_sync, &rdev->flags))
				continue;

			atomic_inc(&rdev->nr_pending);
			rcu_read_unlock();
			if (r10_sync_page_io(rdev,
					     r10_bio->devs[sl].addr +
					     sect,
					     s, conf->tmppage, WRITE)
			    == 0) {
				/* Well, this device is dead */
				pr_notice("md/raid10:%s: read correction write failed (%d sectors at %llu on %s)\n",
					  mdname(mddev), s,
					  (unsigned long long)(
						  sect +
						  choose_data_offset(r10_bio,
								     rdev)),
					  bdevname(rdev->bdev, b));
				pr_notice("md/raid10:%s: %s: failing drive\n",
					  mdname(mddev),
					  bdevname(rdev->bdev, b));
			}
			rdev_dec_pending(rdev, mddev);
			rcu_read_lock();
		}
		sl = start;
		while (sl != r10_bio->read_slot) {
			char b[BDEVNAME_SIZE];

			if (sl==0)
				sl = conf->copies;
			sl--;
			d = r10_bio->devs[sl].devnum;
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			if (!rdev ||
			    test_bit(Faulty, &rdev->flags) ||
			    !test_bit(In_sync, &rdev->flags))
				continue;

			atomic_inc(&rdev->nr_pending);
			rcu_read_unlock();
			switch (r10_sync_page_io(rdev,
					     r10_bio->devs[sl].addr +
					     sect,
					     s, conf->tmppage,
						 READ)) {
			case 0:
				/* Well, this device is dead */
				pr_notice("md/raid10:%s: unable to read back corrected sectors (%d sectors at %llu on %s)\n",
				       mdname(mddev), s,
				       (unsigned long long)(
					       sect +
					       choose_data_offset(r10_bio, rdev)),
				       bdevname(rdev->bdev, b));
				pr_notice("md/raid10:%s: %s: failing drive\n",
				       mdname(mddev),
				       bdevname(rdev->bdev, b));
				break;
			case 1:
				pr_info("md/raid10:%s: read error corrected (%d sectors at %llu on %s)\n",
				       mdname(mddev), s,
				       (unsigned long long)(
					       sect +
					       choose_data_offset(r10_bio, rdev)),
				       bdevname(rdev->bdev, b));
				atomic_add(s, &rdev->corrected_errors);
			}

			rdev_dec_pending(rdev, mddev);
			rcu_read_lock();
		}
		rcu_read_unlock();

		sectors -= s;
		sect += s;
	}
}