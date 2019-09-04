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
struct r1conf {int raid_disks; TYPE_1__* mirrors; TYPE_2__* mddev; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {scalar_t__ degraded; } ;
struct TYPE_3__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_conf(struct r1conf *conf)
{
	int i;

	pr_debug("RAID1 conf printout:\n");
	if (!conf) {
		pr_debug("(!conf)\n");
		return;
	}
	pr_debug(" --- wd:%d rd:%d\n", conf->raid_disks - conf->mddev->degraded,
		 conf->raid_disks);

	rcu_read_lock();
	for (i = 0; i < conf->raid_disks; i++) {
		char b[BDEVNAME_SIZE];
		struct md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		if (rdev)
			pr_debug(" disk %d, wo:%d, o:%d, dev:%s\n",
				 i, !test_bit(In_sync, &rdev->flags),
				 !test_bit(Faulty, &rdev->flags),
				 bdevname(rdev->bdev,b));
	}
	rcu_read_unlock();
}