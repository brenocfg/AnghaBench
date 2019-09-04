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
typedef  scalar_t__ uint64_t ;
struct md_rdev {int /*<<< orphan*/  sb_page; TYPE_1__* mddev; int /*<<< orphan*/  flags; int /*<<< orphan*/  recovery_offset; int /*<<< orphan*/  sb_size; } ;
struct dm_raid_superblock {scalar_t__ magic; int /*<<< orphan*/  events; scalar_t__ compat_features; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RAID_MAGIC ; 
 int /*<<< orphan*/  FEATURE_FLAG_SUPPORTS_V190 ; 
 int /*<<< orphan*/  FirstUse ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct dm_raid_superblock* page_address (int /*<<< orphan*/ ) ; 
 int read_disk_sb (struct md_rdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  super_sync (TYPE_1__*,struct md_rdev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int super_load(struct md_rdev *rdev, struct md_rdev *refdev)
{
	int r;
	struct dm_raid_superblock *sb;
	struct dm_raid_superblock *refsb;
	uint64_t events_sb, events_refsb;

	r = read_disk_sb(rdev, rdev->sb_size, false);
	if (r)
		return r;

	sb = page_address(rdev->sb_page);

	/*
	 * Two cases that we want to write new superblocks and rebuild:
	 * 1) New device (no matching magic number)
	 * 2) Device specified for rebuild (!In_sync w/ offset == 0)
	 */
	if ((sb->magic != cpu_to_le32(DM_RAID_MAGIC)) ||
	    (!test_bit(In_sync, &rdev->flags) && !rdev->recovery_offset)) {
		super_sync(rdev->mddev, rdev);

		set_bit(FirstUse, &rdev->flags);
		sb->compat_features = cpu_to_le32(FEATURE_FLAG_SUPPORTS_V190);

		/* Force writing of superblocks to disk */
		set_bit(MD_SB_CHANGE_DEVS, &rdev->mddev->sb_flags);

		/* Any superblock is better than none, choose that if given */
		return refdev ? 0 : 1;
	}

	if (!refdev)
		return 1;

	events_sb = le64_to_cpu(sb->events);

	refsb = page_address(refdev->sb_page);
	events_refsb = le64_to_cpu(refsb->events);

	return (events_sb > events_refsb) ? 1 : 0;
}