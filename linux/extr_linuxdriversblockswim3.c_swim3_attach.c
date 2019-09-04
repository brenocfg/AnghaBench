#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct of_device_id {int dummy; } ;
struct macio_dev {int dummy; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; TYPE_1__* queue; } ;
struct TYPE_3__ {int /*<<< orphan*/ * queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_HIGH ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FLOPPY_MAJOR ; 
 int /*<<< orphan*/  GENHD_FL_REMOVABLE ; 
 int MAX_FLOPPIES ; 
 int /*<<< orphan*/  add_disk (struct gendisk*) ; 
 struct gendisk* alloc_disk (int) ; 
 TYPE_1__* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct gendisk** disks ; 
 int /*<<< orphan*/  do_fd_request ; 
 int /*<<< orphan*/  floppy_count ; 
 int /*<<< orphan*/  floppy_fops ; 
 int /*<<< orphan*/ * floppy_states ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 scalar_t__ register_blkdev (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int swim3_add_device (struct macio_dev*,int) ; 
 int /*<<< orphan*/  swim3_lock ; 

__attribute__((used)) static int swim3_attach(struct macio_dev *mdev,
			const struct of_device_id *match)
{
	struct gendisk *disk;
	int index, rc;

	index = floppy_count++;
	if (index >= MAX_FLOPPIES)
		return -ENXIO;

	/* Add the drive */
	rc = swim3_add_device(mdev, index);
	if (rc)
		return rc;
	/* Now register that disk. Same comment about failure handling */
	disk = disks[index] = alloc_disk(1);
	if (disk == NULL)
		return -ENOMEM;
	disk->queue = blk_init_queue(do_fd_request, &swim3_lock);
	if (disk->queue == NULL) {
		put_disk(disk);
		return -ENOMEM;
	}
	blk_queue_bounce_limit(disk->queue, BLK_BOUNCE_HIGH);
	disk->queue->queuedata = &floppy_states[index];

	if (index == 0) {
		/* If we failed, there isn't much we can do as the driver is still
		 * too dumb to remove the device, just bail out
		 */
		if (register_blkdev(FLOPPY_MAJOR, "fd"))
			return 0;
	}

	disk->major = FLOPPY_MAJOR;
	disk->first_minor = index;
	disk->fops = &floppy_fops;
	disk->private_data = &floppy_states[index];
	disk->flags |= GENHD_FL_REMOVABLE;
	sprintf(disk->disk_name, "fd%d", index);
	set_capacity(disk, 2880);
	add_disk(disk);

	return 0;
}