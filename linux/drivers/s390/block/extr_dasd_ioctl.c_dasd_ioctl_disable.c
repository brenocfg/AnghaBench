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
struct dasd_device {int dummy; } ;
struct block_device {int /*<<< orphan*/  bd_mutex; int /*<<< orphan*/  bd_inode; int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DASD_STATE_BASIC ; 
 int EACCES ; 
 int ENODEV ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct dasd_device* dasd_device_from_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_set_target_state (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dasd_ioctl_disable(struct block_device *bdev)
{
	struct dasd_device *base;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	if (!base)
		return -ENODEV;
	/*
	 * Man this is sick. We don't do a real disable but only downgrade
	 * the device to DASD_STATE_BASIC. The reason is that dasdfmt uses
	 * BIODASDDISABLE to disable accesses to the device via the block
	 * device layer but it still wants to do i/o on the device by
	 * using the BIODASDFMT ioctl. Therefore the correct state for the
	 * device is DASD_STATE_BASIC that allows to do basic i/o.
	 */
	dasd_set_target_state(base, DASD_STATE_BASIC);
	/*
	 * Set i_size to zero, since read, write, etc. check against this
	 * value.
	 */
	mutex_lock(&bdev->bd_mutex);
	i_size_write(bdev->bd_inode, 0);
	mutex_unlock(&bdev->bd_mutex);
	dasd_put_device(base);
	return 0;
}