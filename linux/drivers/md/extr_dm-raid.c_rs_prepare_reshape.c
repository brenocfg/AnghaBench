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
struct mddev {scalar_t__ raid_disks; int degraded; int /*<<< orphan*/  layout; int /*<<< orphan*/  new_layout; } ;
struct raid_set {scalar_t__ raid_disks; scalar_t__ raid10_copies; int delta_disks; int /*<<< orphan*/  runtime_flags; TYPE_1__* ti; struct mddev md; } ;
struct TYPE_2__ {char* error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGORITHM_RAID10_NEAR ; 
 int EINVAL ; 
 int /*<<< orphan*/  RT_FLAG_RESHAPE_RS ; 
 int /*<<< orphan*/  RT_FLAG_UPDATE_SBS ; 
 scalar_t__ __is_raid10_near (int /*<<< orphan*/ ) ; 
 scalar_t__ __raid10_near_copies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __reorder_raid_disk_indexes (struct raid_set*) ; 
 int /*<<< orphan*/  raid10_format_to_md_layout (struct raid_set*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rs_is_raid1 (struct raid_set*) ; 
 scalar_t__ rs_is_raid10 (struct raid_set*) ; 
 scalar_t__ rs_is_raid456 (struct raid_set*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rs_prepare_reshape(struct raid_set *rs)
{
	bool reshape;
	struct mddev *mddev = &rs->md;

	if (rs_is_raid10(rs)) {
		if (rs->raid_disks != mddev->raid_disks &&
		    __is_raid10_near(mddev->layout) &&
		    rs->raid10_copies &&
		    rs->raid10_copies != __raid10_near_copies(mddev->layout)) {
			/*
			 * raid disk have to be multiple of data copies to allow this conversion,
			 *
			 * This is actually not a reshape it is a
			 * rebuild of any additional mirrors per group
			 */
			if (rs->raid_disks % rs->raid10_copies) {
				rs->ti->error = "Can't reshape raid10 mirror groups";
				return -EINVAL;
			}

			/* Userpace reordered disks to add/remove mirrors -> adjust raid_disk indexes */
			__reorder_raid_disk_indexes(rs);
			mddev->layout = raid10_format_to_md_layout(rs, ALGORITHM_RAID10_NEAR,
								   rs->raid10_copies);
			mddev->new_layout = mddev->layout;
			reshape = false;
		} else
			reshape = true;

	} else if (rs_is_raid456(rs))
		reshape = true;

	else if (rs_is_raid1(rs)) {
		if (rs->delta_disks) {
			/* Process raid1 via delta_disks */
			mddev->degraded = rs->delta_disks < 0 ? -rs->delta_disks : rs->delta_disks;
			reshape = true;
		} else {
			/* Process raid1 without delta_disks */
			mddev->raid_disks = rs->raid_disks;
			reshape = false;
		}
	} else {
		rs->ti->error = "Called with bogus raid type";
		return -EINVAL;
	}

	if (reshape) {
		set_bit(RT_FLAG_RESHAPE_RS, &rs->runtime_flags);
		set_bit(RT_FLAG_UPDATE_SBS, &rs->runtime_flags);
	} else if (mddev->raid_disks < rs->raid_disks)
		/* Create new superblocks and bitmaps, if any new disks */
		set_bit(RT_FLAG_UPDATE_SBS, &rs->runtime_flags);

	return 0;
}