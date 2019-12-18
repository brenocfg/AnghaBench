#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct dmz_target {TYPE_1__* ddev; struct dmz_dev* dev; } ;
struct dmz_dev {int capacity; TYPE_3__* bdev; int /*<<< orphan*/  nr_zones; scalar_t__ zone_nr_blocks; void* zone_nr_blocks_shift; scalar_t__ zone_nr_sectors; void* zone_nr_sectors_shift; int /*<<< orphan*/  name; } ;
struct dm_target {char* error; int len; scalar_t__ begin; int /*<<< orphan*/  table; struct dmz_target* private; } ;
typedef  int sector_t ;
struct TYPE_8__ {int /*<<< orphan*/  bd_inode; } ;
struct TYPE_7__ {TYPE_3__* bdev; } ;

/* Variables and functions */
 scalar_t__ BLK_ZONED_NONE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SECTOR_SHIFT ; 
 struct request_queue* bdev_get_queue (TYPE_3__*) ; 
 scalar_t__ bdev_zoned_model (TYPE_3__*) ; 
 int /*<<< orphan*/  bdevname (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_zone_sectors (struct request_queue*) ; 
 int /*<<< orphan*/  blkdev_nr_zones (TYPE_3__*) ; 
 int dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,TYPE_1__*) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ dmz_sect2blk (scalar_t__) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 void* ilog2 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dmz_dev*) ; 
 struct dmz_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmz_get_zoned_device(struct dm_target *ti, char *path)
{
	struct dmz_target *dmz = ti->private;
	struct request_queue *q;
	struct dmz_dev *dev;
	sector_t aligned_capacity;
	int ret;

	/* Get the target device */
	ret = dm_get_device(ti, path, dm_table_get_mode(ti->table), &dmz->ddev);
	if (ret) {
		ti->error = "Get target device failed";
		dmz->ddev = NULL;
		return ret;
	}

	dev = kzalloc(sizeof(struct dmz_dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err;
	}

	dev->bdev = dmz->ddev->bdev;
	(void)bdevname(dev->bdev, dev->name);

	if (bdev_zoned_model(dev->bdev) == BLK_ZONED_NONE) {
		ti->error = "Not a zoned block device";
		ret = -EINVAL;
		goto err;
	}

	q = bdev_get_queue(dev->bdev);
	dev->capacity = i_size_read(dev->bdev->bd_inode) >> SECTOR_SHIFT;
	aligned_capacity = dev->capacity &
				~((sector_t)blk_queue_zone_sectors(q) - 1);
	if (ti->begin ||
	    ((ti->len != dev->capacity) && (ti->len != aligned_capacity))) {
		ti->error = "Partial mapping not supported";
		ret = -EINVAL;
		goto err;
	}

	dev->zone_nr_sectors = blk_queue_zone_sectors(q);
	dev->zone_nr_sectors_shift = ilog2(dev->zone_nr_sectors);

	dev->zone_nr_blocks = dmz_sect2blk(dev->zone_nr_sectors);
	dev->zone_nr_blocks_shift = ilog2(dev->zone_nr_blocks);

	dev->nr_zones = blkdev_nr_zones(dev->bdev);

	dmz->dev = dev;

	return 0;
err:
	dm_put_device(ti, dmz->ddev);
	kfree(dev);

	return ret;
}