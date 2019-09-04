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
struct TYPE_3__ {int raid_disks; } ;
struct raid_set {TYPE_2__* dev; TYPE_1__ md; } ;
struct md_rdev {scalar_t__ sectors; scalar_t__ bdev; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {struct md_rdev rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Journal ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sector_t __rdev_sectors(struct raid_set *rs)
{
	int i;

	for (i = 0; i < rs->md.raid_disks; i++) {
		struct md_rdev *rdev = &rs->dev[i].rdev;

		if (!test_bit(Journal, &rdev->flags) &&
		    rdev->bdev && rdev->sectors)
			return rdev->sectors;
	}

	return 0;
}