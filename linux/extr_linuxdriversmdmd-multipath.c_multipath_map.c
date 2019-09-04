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
struct mpconf {int raid_disks; TYPE_1__* multipaths; } ;
struct md_rdev {int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit_ratelimited (char*) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multipath_map (struct mpconf *conf)
{
	int i, disks = conf->raid_disks;

	/*
	 * Later we do read balancing on the read side
	 * now we use the first available disk.
	 */

	rcu_read_lock();
	for (i = 0; i < disks; i++) {
		struct md_rdev *rdev = rcu_dereference(conf->multipaths[i].rdev);
		if (rdev && test_bit(In_sync, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags)) {
			atomic_inc(&rdev->nr_pending);
			rcu_read_unlock();
			return i;
		}
	}
	rcu_read_unlock();

	pr_crit_ratelimited("multipath_map(): no more operational IO paths?\n");
	return (-1);
}