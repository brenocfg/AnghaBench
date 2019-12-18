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
struct uio_listener {struct uio_device* dev; } ;
struct uio_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  info_lock; TYPE_1__* info; } ;
struct inode {int dummy; } ;
struct file {struct uio_listener* private_data; } ;
struct TYPE_2__ {int (* release ) (TYPE_1__*,struct inode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uio_listener*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,struct inode*) ; 

__attribute__((used)) static int uio_release(struct inode *inode, struct file *filep)
{
	int ret = 0;
	struct uio_listener *listener = filep->private_data;
	struct uio_device *idev = listener->dev;

	mutex_lock(&idev->info_lock);
	if (idev->info && idev->info->release)
		ret = idev->info->release(idev->info, inode);
	mutex_unlock(&idev->info_lock);

	module_put(idev->owner);
	kfree(listener);
	put_device(&idev->dev);
	return ret;
}