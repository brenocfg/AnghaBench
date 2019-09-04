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
struct r1conf {int raid_disks; int /*<<< orphan*/  tmppage; TYPE_1__* mirrors; struct mddev* mddev; } ;
struct mddev {int dummy; } ;
struct md_rdev {scalar_t__ recovery_offset; scalar_t__ data_offset; int /*<<< orphan*/  bdev; int /*<<< orphan*/  corrected_errors; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_badblock (struct md_rdev*,scalar_t__,int,scalar_t__*,int*) ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ r1_sync_page_io (struct md_rdev*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct md_rdev* rcu_dereference (struct md_rdev*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  rdev_set_badblocks (struct md_rdev*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sync_page_io (struct md_rdev*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fix_read_error(struct r1conf *conf, int read_disk,
			   sector_t sect, int sectors)
{
	struct mddev *mddev = conf->mddev;
	while(sectors) {
		int s = sectors;
		int d = read_disk;
		int success = 0;
		int start;
		struct md_rdev *rdev;

		if (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;

		do {
			sector_t first_bad;
			int bad_sectors;

			rcu_read_lock();
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			if (rdev &&
			    (test_bit(In_sync, &rdev->flags) ||
			     (!test_bit(Faulty, &rdev->flags) &&
			      rdev->recovery_offset >= sect + s)) &&
			    is_badblock(rdev, sect, s,
					&first_bad, &bad_sectors) == 0) {
				atomic_inc(&rdev->nr_pending);
				rcu_read_unlock();
				if (sync_page_io(rdev, sect, s<<9,
					 conf->tmppage, REQ_OP_READ, 0, false))
					success = 1;
				rdev_dec_pending(rdev, mddev);
				if (success)
					break;
			} else
				rcu_read_unlock();
			d++;
			if (d == conf->raid_disks * 2)
				d = 0;
		} while (!success && d != read_disk);

		if (!success) {
			/* Cannot read from anywhere - mark it bad */
			struct md_rdev *rdev = conf->mirrors[read_disk].rdev;
			if (!rdev_set_badblocks(rdev, sect, s, 0))
				md_error(mddev, rdev);
			break;
		}
		/* write it back and re-read */
		start = d;
		while (d != read_disk) {
			if (d==0)
				d = conf->raid_disks * 2;
			d--;
			rcu_read_lock();
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			if (rdev &&
			    !test_bit(Faulty, &rdev->flags)) {
				atomic_inc(&rdev->nr_pending);
				rcu_read_unlock();
				r1_sync_page_io(rdev, sect, s,
						conf->tmppage, WRITE);
				rdev_dec_pending(rdev, mddev);
			} else
				rcu_read_unlock();
		}
		d = start;
		while (d != read_disk) {
			char b[BDEVNAME_SIZE];
			if (d==0)
				d = conf->raid_disks * 2;
			d--;
			rcu_read_lock();
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			if (rdev &&
			    !test_bit(Faulty, &rdev->flags)) {
				atomic_inc(&rdev->nr_pending);
				rcu_read_unlock();
				if (r1_sync_page_io(rdev, sect, s,
						    conf->tmppage, READ)) {
					atomic_add(s, &rdev->corrected_errors);
					pr_info("md/raid1:%s: read error corrected (%d sectors at %llu on %s)\n",
						mdname(mddev), s,
						(unsigned long long)(sect +
								     rdev->data_offset),
						bdevname(rdev->bdev, b));
				}
				rdev_dec_pending(rdev, mddev);
			} else
				rcu_read_unlock();
		}
		sectors -= s;
		sect += s;
	}
}