#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hd_struct {int dummy; } ;
struct TYPE_6__ {void* holder_dir; } ;
struct gendisk {int flags; TYPE_4__* queue; void* slave_dir; TYPE_1__ part0; int /*<<< orphan*/  disk_name; } ;
struct disk_part_iter {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; struct device* parent; } ;
struct block_device {int bd_invalidated; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_3__* backing_dev_info; } ;
struct TYPE_8__ {TYPE_2__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 int GENHD_FL_HIDDEN ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct block_device* bdget_disk (struct gendisk*,int /*<<< orphan*/ ) ; 
 int blkdev_get (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * block_depr ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (struct device*,int) ; 
 scalar_t__ device_add (struct device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  disk_part_iter_exit (struct disk_part_iter*) ; 
 int /*<<< orphan*/  disk_part_iter_init (struct disk_part_iter*,struct gendisk*,int /*<<< orphan*/ ) ; 
 struct hd_struct* disk_part_iter_next (struct disk_part_iter*) ; 
 int /*<<< orphan*/  disk_part_scan_enabled (struct gendisk*) ; 
 struct device* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  get_capacity (struct gendisk*) ; 
 void* kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 char* kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* part_to_dev (struct hd_struct*) ; 
 int /*<<< orphan*/  pm_runtime_set_memalloc_noio (struct device*,int) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_deprecated ; 

__attribute__((used)) static void register_disk(struct device *parent, struct gendisk *disk)
{
	struct device *ddev = disk_to_dev(disk);
	struct block_device *bdev;
	struct disk_part_iter piter;
	struct hd_struct *part;
	int err;

	ddev->parent = parent;

	dev_set_name(ddev, "%s", disk->disk_name);

	/* delay uevents, until we scanned partition table */
	dev_set_uevent_suppress(ddev, 1);

	if (device_add(ddev))
		return;
	if (!sysfs_deprecated) {
		err = sysfs_create_link(block_depr, &ddev->kobj,
					kobject_name(&ddev->kobj));
		if (err) {
			device_del(ddev);
			return;
		}
	}

	/*
	 * avoid probable deadlock caused by allocating memory with
	 * GFP_KERNEL in runtime_resume callback of its all ancestor
	 * devices
	 */
	pm_runtime_set_memalloc_noio(ddev, true);

	disk->part0.holder_dir = kobject_create_and_add("holders", &ddev->kobj);
	disk->slave_dir = kobject_create_and_add("slaves", &ddev->kobj);

	if (disk->flags & GENHD_FL_HIDDEN) {
		dev_set_uevent_suppress(ddev, 0);
		return;
	}

	/* No minors to use for partitions */
	if (!disk_part_scan_enabled(disk))
		goto exit;

	/* No such device (e.g., media were just removed) */
	if (!get_capacity(disk))
		goto exit;

	bdev = bdget_disk(disk, 0);
	if (!bdev)
		goto exit;

	bdev->bd_invalidated = 1;
	err = blkdev_get(bdev, FMODE_READ, NULL);
	if (err < 0)
		goto exit;
	blkdev_put(bdev, FMODE_READ);

exit:
	/* announce disk after possible partitions are created */
	dev_set_uevent_suppress(ddev, 0);
	kobject_uevent(&ddev->kobj, KOBJ_ADD);

	/* announce possible partitions */
	disk_part_iter_init(&piter, disk, 0);
	while ((part = disk_part_iter_next(&piter)))
		kobject_uevent(&part_to_dev(part)->kobj, KOBJ_ADD);
	disk_part_iter_exit(&piter);

	err = sysfs_create_link(&ddev->kobj,
				&disk->queue->backing_dev_info->dev->kobj,
				"bdi");
	WARN_ON(err);
}