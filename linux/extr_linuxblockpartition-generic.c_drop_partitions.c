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
struct hd_struct {int /*<<< orphan*/  partno; } ;
struct gendisk {int dummy; } ;
struct disk_part_iter {int dummy; } ;
struct block_device {scalar_t__ bd_super; scalar_t__ bd_part_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_PITER_INCL_EMPTY ; 
 int EBUSY ; 
 int /*<<< orphan*/  delete_partition (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_part_iter_exit (struct disk_part_iter*) ; 
 int /*<<< orphan*/  disk_part_iter_init (struct disk_part_iter*,struct gendisk*,int /*<<< orphan*/ ) ; 
 struct hd_struct* disk_part_iter_next (struct disk_part_iter*) ; 
 int invalidate_partition (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drop_partitions(struct gendisk *disk, struct block_device *bdev)
{
	struct disk_part_iter piter;
	struct hd_struct *part;
	int res;

	if (bdev->bd_part_count || bdev->bd_super)
		return -EBUSY;
	res = invalidate_partition(disk, 0);
	if (res)
		return res;

	disk_part_iter_init(&piter, disk, DISK_PITER_INCL_EMPTY);
	while ((part = disk_part_iter_next(&piter)))
		delete_partition(disk, part->partno);
	disk_part_iter_exit(&piter);

	return 0;
}