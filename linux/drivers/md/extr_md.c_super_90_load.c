#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct TYPE_11__ {int shift; } ;
struct md_rdev {int sb_start; int desc_nr; int sectors; int /*<<< orphan*/  bdev; int /*<<< orphan*/  sb_page; TYPE_1__ badblocks; int /*<<< orphan*/  sb_size; scalar_t__ new_data_offset; scalar_t__ data_offset; int /*<<< orphan*/  preferred_minor; } ;
typedef  int sector_t ;
struct TYPE_12__ {int number; } ;
struct TYPE_13__ {scalar_t__ md_magic; int minor_version; scalar_t__ raid_disks; int level; scalar_t__ size; TYPE_2__ this_disk; int /*<<< orphan*/  md_minor; int /*<<< orphan*/  sb_csum; int /*<<< orphan*/  major_version; } ;
typedef  TYPE_3__ mdp_super_t ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int EINVAL ; 
 int LEVEL_MULTIPATH ; 
 int /*<<< orphan*/  MD_SB_BYTES ; 
 scalar_t__ MD_SB_MAGIC ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int calc_dev_sboffset (struct md_rdev*) ; 
 int /*<<< orphan*/  calc_sb_csum (TYPE_3__*) ; 
 scalar_t__ md_csum_fold (int /*<<< orphan*/ ) ; 
 scalar_t__ md_event (TYPE_3__*) ; 
 int /*<<< orphan*/  md_sb_equal (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  md_uuid_equal (TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,...) ; 
 int read_disk_sb (struct md_rdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int super_90_load(struct md_rdev *rdev, struct md_rdev *refdev, int minor_version)
{
	char b[BDEVNAME_SIZE], b2[BDEVNAME_SIZE];
	mdp_super_t *sb;
	int ret;

	/*
	 * Calculate the position of the superblock (512byte sectors),
	 * it's at the end of the disk.
	 *
	 * It also happens to be a multiple of 4Kb.
	 */
	rdev->sb_start = calc_dev_sboffset(rdev);

	ret = read_disk_sb(rdev, MD_SB_BYTES);
	if (ret)
		return ret;

	ret = -EINVAL;

	bdevname(rdev->bdev, b);
	sb = page_address(rdev->sb_page);

	if (sb->md_magic != MD_SB_MAGIC) {
		pr_warn("md: invalid raid superblock magic on %s\n", b);
		goto abort;
	}

	if (sb->major_version != 0 ||
	    sb->minor_version < 90 ||
	    sb->minor_version > 91) {
		pr_warn("Bad version number %d.%d on %s\n",
			sb->major_version, sb->minor_version, b);
		goto abort;
	}

	if (sb->raid_disks <= 0)
		goto abort;

	if (md_csum_fold(calc_sb_csum(sb)) != md_csum_fold(sb->sb_csum)) {
		pr_warn("md: invalid superblock checksum on %s\n", b);
		goto abort;
	}

	rdev->preferred_minor = sb->md_minor;
	rdev->data_offset = 0;
	rdev->new_data_offset = 0;
	rdev->sb_size = MD_SB_BYTES;
	rdev->badblocks.shift = -1;

	if (sb->level == LEVEL_MULTIPATH)
		rdev->desc_nr = -1;
	else
		rdev->desc_nr = sb->this_disk.number;

	if (!refdev) {
		ret = 1;
	} else {
		__u64 ev1, ev2;
		mdp_super_t *refsb = page_address(refdev->sb_page);
		if (!md_uuid_equal(refsb, sb)) {
			pr_warn("md: %s has different UUID to %s\n",
				b, bdevname(refdev->bdev,b2));
			goto abort;
		}
		if (!md_sb_equal(refsb, sb)) {
			pr_warn("md: %s has same UUID but different superblock to %s\n",
				b, bdevname(refdev->bdev, b2));
			goto abort;
		}
		ev1 = md_event(sb);
		ev2 = md_event(refsb);
		if (ev1 > ev2)
			ret = 1;
		else
			ret = 0;
	}
	rdev->sectors = rdev->sb_start;
	/* Limit to 4TB as metadata cannot record more than that.
	 * (not needed for Linear and RAID0 as metadata doesn't
	 * record this size)
	 */
	if ((u64)rdev->sectors >= (2ULL << 32) && sb->level >= 1)
		rdev->sectors = (sector_t)(2ULL << 32) - 2;

	if (rdev->sectors < ((sector_t)sb->size) * 2 && sb->level >= 1)
		/* "this cannot possibly happen" ... */
		ret = -EINVAL;

 abort:
	return ret;
}