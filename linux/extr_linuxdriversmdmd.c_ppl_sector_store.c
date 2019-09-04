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
struct TYPE_4__ {unsigned long long offset; unsigned long long sector; } ;
struct md_rdev {scalar_t__ raid_disk; unsigned long long sb_start; TYPE_2__ ppl; TYPE_1__* mddev; } ;
typedef  size_t ssize_t ;
typedef  unsigned long long sector_t ;
struct TYPE_3__ {scalar_t__ major_version; int /*<<< orphan*/  external; scalar_t__ persistent; int /*<<< orphan*/  flags; scalar_t__ pers; } ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  MD_HAS_PPL ; 
 unsigned long long S16_MAX ; 
 unsigned long long S16_MIN ; 
 scalar_t__ kstrtoull (char const*,int,unsigned long long*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
ppl_sector_store(struct md_rdev *rdev, const char *buf, size_t len)
{
	unsigned long long sector;

	if (kstrtoull(buf, 10, &sector) < 0)
		return -EINVAL;
	if (sector != (sector_t)sector)
		return -EINVAL;

	if (rdev->mddev->pers && test_bit(MD_HAS_PPL, &rdev->mddev->flags) &&
	    rdev->raid_disk >= 0)
		return -EBUSY;

	if (rdev->mddev->persistent) {
		if (rdev->mddev->major_version == 0)
			return -EINVAL;
		if ((sector > rdev->sb_start &&
		     sector - rdev->sb_start > S16_MAX) ||
		    (sector < rdev->sb_start &&
		     rdev->sb_start - sector > -S16_MIN))
			return -EINVAL;
		rdev->ppl.offset = sector - rdev->sb_start;
	} else if (!rdev->mddev->external) {
		return -EBUSY;
	}
	rdev->ppl.sector = sector;
	return len;
}