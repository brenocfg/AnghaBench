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
struct file {struct block_device* private_data; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 long blkdev_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 

__attribute__((used)) static long
raw_ioctl(struct file *filp, unsigned int command, unsigned long arg)
{
	struct block_device *bdev = filp->private_data;
	return blkdev_ioctl(bdev, 0, command, arg);
}