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
struct gendisk {int dummy; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int __invalidate_device (struct block_device*,int) ; 
 struct block_device* bdget_disk (struct gendisk*,int) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  fsync_bdev (struct block_device*) ; 

int invalidate_partition(struct gendisk *disk, int partno)
{
	int res = 0;
	struct block_device *bdev = bdget_disk(disk, partno);
	if (bdev) {
		fsync_bdev(bdev);
		res = __invalidate_device(bdev, true);
		bdput(bdev);
	}
	return res;
}