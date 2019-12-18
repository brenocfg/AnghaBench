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
struct dasd_block {struct block_device* bdev; int /*<<< orphan*/  base; int /*<<< orphan*/  gdp; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int ENODEV ; 
 int /*<<< orphan*/  FMODE_READ ; 
 struct block_device* bdget_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int blkdev_get (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int blkdev_reread_part (struct block_device*) ; 

int dasd_scan_partitions(struct dasd_block *block)
{
	struct block_device *bdev;
	int rc;

	bdev = bdget_disk(block->gdp, 0);
	if (!bdev) {
		DBF_DEV_EVENT(DBF_ERR, block->base, "%s",
			      "scan partitions error, bdget returned NULL");
		return -ENODEV;
	}

	rc = blkdev_get(bdev, FMODE_READ, NULL);
	if (rc < 0) {
		DBF_DEV_EVENT(DBF_ERR, block->base,
			      "scan partitions error, blkdev_get returned %d",
			      rc);
		return -ENODEV;
	}

	rc = blkdev_reread_part(bdev);
	if (rc)
		DBF_DEV_EVENT(DBF_ERR, block->base,
				"scan partitions error, rc %d", rc);

	/*
	 * Since the matching blkdev_put call to the blkdev_get in
	 * this function is not called before dasd_destroy_partitions
	 * the offline open_count limit needs to be increased from
	 * 0 to 1. This is done by setting device->bdev (see
	 * dasd_generic_set_offline). As long as the partition
	 * detection is running no offline should be allowed. That
	 * is why the assignment to device->bdev is done AFTER
	 * the BLKRRPART ioctl.
	 */
	block->bdev = bdev;
	return 0;
}