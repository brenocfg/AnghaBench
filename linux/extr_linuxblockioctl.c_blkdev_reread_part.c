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
struct block_device {int /*<<< orphan*/  bd_mutex; } ;

/* Variables and functions */
 int __blkdev_reread_part (struct block_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int blkdev_reread_part(struct block_device *bdev)
{
	int res;

	mutex_lock(&bdev->bd_mutex);
	res = __blkdev_reread_part(bdev);
	mutex_unlock(&bdev->bd_mutex);

	return res;
}