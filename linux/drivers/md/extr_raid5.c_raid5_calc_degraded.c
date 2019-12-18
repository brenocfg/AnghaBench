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
struct r5conf {int previous_raid_disks; int raid_disks; TYPE_1__* disks; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  replacement; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int raid5_calc_degraded(struct r5conf *conf)
{
	int degraded, degraded2;
	int i;

	rcu_read_lock();
	degraded = 0;
	for (i = 0; i < conf->previous_raid_disks; i++) {
		struct md_rdev *rdev = rcu_dereference(conf->disks[i].rdev);
		if (rdev && test_bit(Faulty, &rdev->flags))
			rdev = rcu_dereference(conf->disks[i].replacement);
		if (!rdev || test_bit(Faulty, &rdev->flags))
			degraded++;
		else if (test_bit(In_sync, &rdev->flags))
			;
		else
			/* not in-sync or faulty.
			 * If the reshape increases the number of devices,
			 * this is being recovered by the reshape, so
			 * this 'previous' section is not in_sync.
			 * If the number of devices is being reduced however,
			 * the device can only be part of the array if
			 * we are reverting a reshape, so this section will
			 * be in-sync.
			 */
			if (conf->raid_disks >= conf->previous_raid_disks)
				degraded++;
	}
	rcu_read_unlock();
	if (conf->raid_disks == conf->previous_raid_disks)
		return degraded;
	rcu_read_lock();
	degraded2 = 0;
	for (i = 0; i < conf->raid_disks; i++) {
		struct md_rdev *rdev = rcu_dereference(conf->disks[i].rdev);
		if (rdev && test_bit(Faulty, &rdev->flags))
			rdev = rcu_dereference(conf->disks[i].replacement);
		if (!rdev || test_bit(Faulty, &rdev->flags))
			degraded2++;
		else if (test_bit(In_sync, &rdev->flags))
			;
		else
			/* not in-sync or faulty.
			 * If reshape increases the number of devices, this
			 * section has already been recovered, else it
			 * almost certainly hasn't.
			 */
			if (conf->raid_disks <= conf->previous_raid_disks)
				degraded2++;
	}
	rcu_read_unlock();
	if (degraded2 > degraded)
		return degraded2;
	return degraded;
}