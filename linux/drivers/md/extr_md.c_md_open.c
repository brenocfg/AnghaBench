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
struct mddev {int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  openers; int /*<<< orphan*/  flags; TYPE_1__* gendisk; } ;
struct block_device {TYPE_1__* bd_disk; int /*<<< orphan*/  bd_dev; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct mddev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  MD_CLOSING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_misc_wq ; 
 struct mddev* mddev_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddev_put (struct mddev*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int md_open(struct block_device *bdev, fmode_t mode)
{
	/*
	 * Succeed if we can lock the mddev, which confirms that
	 * it isn't being stopped right now.
	 */
	struct mddev *mddev = mddev_find(bdev->bd_dev);
	int err;

	if (!mddev)
		return -ENODEV;

	if (mddev->gendisk != bdev->bd_disk) {
		/* we are racing with mddev_put which is discarding this
		 * bd_disk.
		 */
		mddev_put(mddev);
		/* Wait until bdev->bd_disk is definitely gone */
		flush_workqueue(md_misc_wq);
		/* Then retry the open from the top */
		return -ERESTARTSYS;
	}
	BUG_ON(mddev != bdev->bd_disk->private_data);

	if ((err = mutex_lock_interruptible(&mddev->open_mutex)))
		goto out;

	if (test_bit(MD_CLOSING, &mddev->flags)) {
		mutex_unlock(&mddev->open_mutex);
		err = -ENODEV;
		goto out;
	}

	err = 0;
	atomic_inc(&mddev->openers);
	mutex_unlock(&mddev->open_mutex);

	check_disk_change(bdev);
 out:
	if (err)
		mddev_put(mddev);
	return err;
}