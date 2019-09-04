#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct block_device {TYPE_1__* bd_inode; int /*<<< orphan*/  bd_dev; } ;
struct TYPE_4__ {char* name; int size; int erasesize; int writesize; int /*<<< orphan*/  index; int /*<<< orphan*/  owner; struct block2mtd_dev* priv; int /*<<< orphan*/  _read; int /*<<< orphan*/  _sync; int /*<<< orphan*/  _write; int /*<<< orphan*/  _erase; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  writebufsize; } ;
struct block2mtd_dev {int /*<<< orphan*/  write_mutex; TYPE_2__ mtd; int /*<<< orphan*/  list; struct block_device* blkdev; } ;
typedef  int fmode_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_3__ {int i_size; } ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MTD_BLOCK_MAJOR ; 
 int /*<<< orphan*/  MTD_CAP_RAM ; 
 int /*<<< orphan*/  MTD_RAM ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct block_device* blkdev_get_by_dev (int /*<<< orphan*/ ,int const,struct block2mtd_dev*) ; 
 struct block_device* blkdev_get_by_path (char*,int const,struct block2mtd_dev*) ; 
 int /*<<< orphan*/  blkmtd_device_list ; 
 int /*<<< orphan*/  block2mtd_erase ; 
 int /*<<< orphan*/  block2mtd_free_device (struct block2mtd_dev*) ; 
 int /*<<< orphan*/  block2mtd_read ; 
 int /*<<< orphan*/  block2mtd_sync ; 
 int /*<<< orphan*/  block2mtd_write ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct block2mtd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mtd_device_register (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_to_dev_t (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  wait_for_device_probe () ; 

__attribute__((used)) static struct block2mtd_dev *add_device(char *devname, int erase_size,
		int timeout)
{
#ifndef MODULE
	int i;
#endif
	const fmode_t mode = FMODE_READ | FMODE_WRITE | FMODE_EXCL;
	struct block_device *bdev;
	struct block2mtd_dev *dev;
	char *name;

	if (!devname)
		return NULL;

	dev = kzalloc(sizeof(struct block2mtd_dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	/* Get a handle on the device */
	bdev = blkdev_get_by_path(devname, mode, dev);

#ifndef MODULE
	/*
	 * We might not have the root device mounted at this point.
	 * Try to resolve the device name by other means.
	 */
	for (i = 0; IS_ERR(bdev) && i <= timeout; i++) {
		dev_t devt;

		if (i)
			/*
			 * Calling wait_for_device_probe in the first loop
			 * was not enough, sleep for a bit in subsequent
			 * go-arounds.
			 */
			msleep(1000);
		wait_for_device_probe();

		devt = name_to_dev_t(devname);
		if (!devt)
			continue;
		bdev = blkdev_get_by_dev(devt, mode, dev);
	}
#endif

	if (IS_ERR(bdev)) {
		pr_err("error: cannot open device %s\n", devname);
		goto err_free_block2mtd;
	}
	dev->blkdev = bdev;

	if (MAJOR(bdev->bd_dev) == MTD_BLOCK_MAJOR) {
		pr_err("attempting to use an MTD device as a block device\n");
		goto err_free_block2mtd;
	}

	if ((long)dev->blkdev->bd_inode->i_size % erase_size) {
		pr_err("erasesize must be a divisor of device size\n");
		goto err_free_block2mtd;
	}

	mutex_init(&dev->write_mutex);

	/* Setup the MTD structure */
	/* make the name contain the block device in */
	name = kasprintf(GFP_KERNEL, "block2mtd: %s", devname);
	if (!name)
		goto err_destroy_mutex;

	dev->mtd.name = name;

	dev->mtd.size = dev->blkdev->bd_inode->i_size & PAGE_MASK;
	dev->mtd.erasesize = erase_size;
	dev->mtd.writesize = 1;
	dev->mtd.writebufsize = PAGE_SIZE;
	dev->mtd.type = MTD_RAM;
	dev->mtd.flags = MTD_CAP_RAM;
	dev->mtd._erase = block2mtd_erase;
	dev->mtd._write = block2mtd_write;
	dev->mtd._sync = block2mtd_sync;
	dev->mtd._read = block2mtd_read;
	dev->mtd.priv = dev;
	dev->mtd.owner = THIS_MODULE;

	if (mtd_device_register(&dev->mtd, NULL, 0)) {
		/* Device didn't get added, so free the entry */
		goto err_destroy_mutex;
	}

	list_add(&dev->list, &blkmtd_device_list);
	pr_info("mtd%d: [%s] erase_size = %dKiB [%d]\n",
		dev->mtd.index,
		dev->mtd.name + strlen("block2mtd: "),
		dev->mtd.erasesize >> 10, dev->mtd.erasesize);
	return dev;

err_destroy_mutex:
	mutex_destroy(&dev->write_mutex);
err_free_block2mtd:
	block2mtd_free_device(dev);
	return NULL;
}