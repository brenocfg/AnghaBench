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
struct dasd_device {TYPE_1__* block; } ;
struct block_device {int /*<<< orphan*/  bd_mutex; int /*<<< orphan*/  bd_inode; int /*<<< orphan*/  bd_disk; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  gdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int ENODEV ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct dasd_device* dasd_device_from_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_enable_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 scalar_t__ get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dasd_ioctl_enable(struct block_device *bdev)
{
	struct dasd_device *base;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	if (!base)
		return -ENODEV;

	dasd_enable_device(base);
	/* Formatting the dasd device can change the capacity. */
	mutex_lock(&bdev->bd_mutex);
	i_size_write(bdev->bd_inode,
		     (loff_t)get_capacity(base->block->gdp) << 9);
	mutex_unlock(&bdev->bd_mutex);
	dasd_put_device(base);
	return 0;
}