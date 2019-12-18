#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct r5conf {int raid_disks; scalar_t__ reshape_progress; scalar_t__ recovery_disabled; int /*<<< orphan*/  r5c_cached_partial_stripes; int /*<<< orphan*/  r5c_cached_full_stripes; int /*<<< orphan*/  active_stripes; scalar_t__ log; struct disk_info* disks; } ;
struct mddev {scalar_t__ recovery_disabled; struct r5conf* private; } ;
struct md_rdev {int raid_disk; int /*<<< orphan*/  flags; int /*<<< orphan*/  nr_pending; } ;
struct disk_info {struct md_rdev* rdev; struct md_rdev* replacement; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  Journal ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  RemoveSynchronized ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_failed (struct r5conf*) ; 
 int /*<<< orphan*/  log_exit (struct r5conf*) ; 
 int log_modify (struct r5conf*,struct md_rdev*,int) ; 
 int /*<<< orphan*/  print_raid5_conf (struct r5conf*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid5_remove_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r5conf *conf = mddev->private;
	int err = 0;
	int number = rdev->raid_disk;
	struct md_rdev **rdevp;
	struct disk_info *p = conf->disks + number;

	print_raid5_conf(conf);
	if (test_bit(Journal, &rdev->flags) && conf->log) {
		/*
		 * we can't wait pending write here, as this is called in
		 * raid5d, wait will deadlock.
		 * neilb: there is no locking about new writes here,
		 * so this cannot be safe.
		 */
		if (atomic_read(&conf->active_stripes) ||
		    atomic_read(&conf->r5c_cached_full_stripes) ||
		    atomic_read(&conf->r5c_cached_partial_stripes)) {
			return -EBUSY;
		}
		log_exit(conf);
		return 0;
	}
	if (rdev == p->rdev)
		rdevp = &p->rdev;
	else if (rdev == p->replacement)
		rdevp = &p->replacement;
	else
		return 0;

	if (number >= conf->raid_disks &&
	    conf->reshape_progress == MaxSector)
		clear_bit(In_sync, &rdev->flags);

	if (test_bit(In_sync, &rdev->flags) ||
	    atomic_read(&rdev->nr_pending)) {
		err = -EBUSY;
		goto abort;
	}
	/* Only remove non-faulty devices if recovery
	 * isn't possible.
	 */
	if (!test_bit(Faulty, &rdev->flags) &&
	    mddev->recovery_disabled != conf->recovery_disabled &&
	    !has_failed(conf) &&
	    (!p->replacement || p->replacement == rdev) &&
	    number < conf->raid_disks) {
		err = -EBUSY;
		goto abort;
	}
	*rdevp = NULL;
	if (!test_bit(RemoveSynchronized, &rdev->flags)) {
		synchronize_rcu();
		if (atomic_read(&rdev->nr_pending)) {
			/* lost the race, try later */
			err = -EBUSY;
			*rdevp = rdev;
		}
	}
	if (!err) {
		err = log_modify(conf, rdev, false);
		if (err)
			goto abort;
	}
	if (p->replacement) {
		/* We must have just cleared 'rdev' */
		p->rdev = p->replacement;
		clear_bit(Replacement, &p->replacement->flags);
		smp_mb(); /* Make sure other CPUs may see both as identical
			   * but will never see neither - if they are careful
			   */
		p->replacement = NULL;

		if (!err)
			err = log_modify(conf, p->rdev, true);
	}

	clear_bit(WantReplacement, &rdev->flags);
abort:

	print_raid5_conf(conf);
	return err;
}