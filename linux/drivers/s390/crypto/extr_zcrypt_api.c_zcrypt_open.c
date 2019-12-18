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
struct ap_perms {int dummy; } ;
struct zcdn_device {struct ap_perms perms; } ;
struct inode {int dummy; } ;
struct file {void* private_data; TYPE_1__* f_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/ * i_cdev; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 struct ap_perms ap_perms ; 
 int /*<<< orphan*/  ap_perms_mutex ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct zcdn_device* find_zcdndev_by_devt (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stream_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  zcrypt_cdev ; 
 int /*<<< orphan*/  zcrypt_open_count ; 

__attribute__((used)) static int zcrypt_open(struct inode *inode, struct file *filp)
{
	struct ap_perms *perms = &ap_perms;

#ifdef CONFIG_ZCRYPT_MULTIDEVNODES
	if (filp->f_inode->i_cdev == &zcrypt_cdev) {
		struct zcdn_device *zcdndev;

		if (mutex_lock_interruptible(&ap_perms_mutex))
			return -ERESTARTSYS;
		zcdndev = find_zcdndev_by_devt(filp->f_inode->i_rdev);
		/* find returns a reference, no get_device() needed */
		mutex_unlock(&ap_perms_mutex);
		if (zcdndev)
			perms = &zcdndev->perms;
	}
#endif
	filp->private_data = (void *) perms;

	atomic_inc(&zcrypt_open_count);
	return stream_open(inode, filp);
}