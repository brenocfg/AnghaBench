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
struct multipath_info {struct md_rdev* rdev; } ;
struct mpconf {struct multipath_info* multipaths; } ;
struct mddev {struct mpconf* private; } ;
struct md_rdev {int raid_disk; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  RemoveSynchronized ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int md_integrity_register (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  print_multipath_conf (struct mpconf*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multipath_remove_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct mpconf *conf = mddev->private;
	int err = 0;
	int number = rdev->raid_disk;
	struct multipath_info *p = conf->multipaths + number;

	print_multipath_conf(conf);

	if (rdev == p->rdev) {
		if (test_bit(In_sync, &rdev->flags) ||
		    atomic_read(&rdev->nr_pending)) {
			pr_warn("hot-remove-disk, slot %d is identified but is still operational!\n", number);
			err = -EBUSY;
			goto abort;
		}
		p->rdev = NULL;
		if (!test_bit(RemoveSynchronized, &rdev->flags)) {
			synchronize_rcu();
			if (atomic_read(&rdev->nr_pending)) {
				/* lost the race, try later */
				err = -EBUSY;
				p->rdev = rdev;
				goto abort;
			}
		}
		err = md_integrity_register(mddev);
	}
abort:

	print_multipath_conf(conf);
	return err;
}