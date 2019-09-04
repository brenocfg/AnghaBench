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
struct raid_set {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ MaxSector ; 
 scalar_t__ __rdev_sectors (struct raid_set*) ; 
 int /*<<< orphan*/  __rs_setup_recovery (struct raid_set*,scalar_t__) ; 

__attribute__((used)) static void rs_setup_recovery(struct raid_set *rs, sector_t dev_sectors)
{
	if (!dev_sectors)
		/* New raid set or 'sync' flag provided */
		__rs_setup_recovery(rs, 0);
	else if (dev_sectors == MaxSector)
		/* Prevent recovery */
		__rs_setup_recovery(rs, MaxSector);
	else if (__rdev_sectors(rs) < dev_sectors)
		/* Grown raid set */
		__rs_setup_recovery(rs, __rdev_sectors(rs));
	else
		__rs_setup_recovery(rs, MaxSector);
}