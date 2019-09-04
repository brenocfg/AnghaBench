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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  amiflop_mutex ; 
 int fd_locked_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fd_ioctl(struct block_device *bdev, fmode_t mode,
			     unsigned int cmd, unsigned long param)
{
	int ret;

	mutex_lock(&amiflop_mutex);
	ret = fd_locked_ioctl(bdev, mode, cmd, param);
	mutex_unlock(&amiflop_mutex);

	return ret;
}