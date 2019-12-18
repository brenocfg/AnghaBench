#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mdp_superblock_1 {int /*<<< orphan*/  sb_csum; void* super_offset; void* data_size; } ;
struct md_rdev {scalar_t__ data_offset; scalar_t__ new_data_offset; scalar_t__ sb_start; unsigned long long sectors; int /*<<< orphan*/  sb_page; int /*<<< orphan*/  sb_size; TYPE_3__* mddev; TYPE_2__* bdev; } ;
typedef  unsigned long long sector_t ;
struct TYPE_5__ {scalar_t__ offset; } ;
struct TYPE_7__ {unsigned long long dev_sectors; TYPE_1__ bitmap_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_sb_1_csum (struct mdp_superblock_1*) ; 
 void* cpu_to_le64 (unsigned long long) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 scalar_t__ md_super_wait (TYPE_3__*) ; 
 int /*<<< orphan*/  md_super_write (TYPE_3__*,struct md_rdev*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp_superblock_1* page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long long
super_1_rdev_size_change(struct md_rdev *rdev, sector_t num_sectors)
{
	struct mdp_superblock_1 *sb;
	sector_t max_sectors;
	if (num_sectors && num_sectors < rdev->mddev->dev_sectors)
		return 0; /* component must fit device */
	if (rdev->data_offset != rdev->new_data_offset)
		return 0; /* too confusing */
	if (rdev->sb_start < rdev->data_offset) {
		/* minor versions 1 and 2; superblock before data */
		max_sectors = i_size_read(rdev->bdev->bd_inode) >> 9;
		max_sectors -= rdev->data_offset;
		if (!num_sectors || num_sectors > max_sectors)
			num_sectors = max_sectors;
	} else if (rdev->mddev->bitmap_info.offset) {
		/* minor version 0 with bitmap we can't move */
		return 0;
	} else {
		/* minor version 0; superblock after data */
		sector_t sb_start;
		sb_start = (i_size_read(rdev->bdev->bd_inode) >> 9) - 8*2;
		sb_start &= ~(sector_t)(4*2 - 1);
		max_sectors = rdev->sectors + sb_start - rdev->sb_start;
		if (!num_sectors || num_sectors > max_sectors)
			num_sectors = max_sectors;
		rdev->sb_start = sb_start;
	}
	sb = page_address(rdev->sb_page);
	sb->data_size = cpu_to_le64(num_sectors);
	sb->super_offset = cpu_to_le64(rdev->sb_start);
	sb->sb_csum = calc_sb_1_csum(sb);
	do {
		md_super_write(rdev->mddev, rdev, rdev->sb_start, rdev->sb_size,
			       rdev->sb_page);
	} while (md_super_wait(rdev->mddev) < 0);
	return num_sectors;

}