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
struct mddev {scalar_t__ new_layout; scalar_t__ layout; scalar_t__ new_chunk_sectors; scalar_t__ chunk_sectors; scalar_t__ raid_disks; } ;
struct raid_set {scalar_t__ delta_disks; scalar_t__ raid_disks; struct mddev md; } ;

/* Variables and functions */
 int /*<<< orphan*/  __is_raid10_far (scalar_t__) ; 
 scalar_t__ rs_is_raid0 (struct raid_set*) ; 
 scalar_t__ rs_is_raid1 (struct raid_set*) ; 
 scalar_t__ rs_is_raid10 (struct raid_set*) ; 
 scalar_t__ rs_takeover_requested (struct raid_set*) ; 

__attribute__((used)) static bool rs_reshape_requested(struct raid_set *rs)
{
	bool change;
	struct mddev *mddev = &rs->md;

	if (rs_takeover_requested(rs))
		return false;

	if (rs_is_raid0(rs))
		return false;

	change = mddev->new_layout != mddev->layout ||
		 mddev->new_chunk_sectors != mddev->chunk_sectors ||
		 rs->delta_disks;

	/* Historical case to support raid1 reshape without delta disks */
	if (rs_is_raid1(rs)) {
		if (rs->delta_disks)
			return !!rs->delta_disks;

		return !change &&
		       mddev->raid_disks != rs->raid_disks;
	}

	if (rs_is_raid10(rs))
		return change &&
		       !__is_raid10_far(mddev->new_layout) &&
		       rs->delta_disks >= 0;

	return change;
}