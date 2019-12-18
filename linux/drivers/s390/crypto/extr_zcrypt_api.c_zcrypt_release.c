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
struct zcdn_device {int /*<<< orphan*/  device; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* f_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/ * i_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_perms_mutex ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct zcdn_device* find_zcdndev_by_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_cdev ; 
 int /*<<< orphan*/  zcrypt_open_count ; 

__attribute__((used)) static int zcrypt_release(struct inode *inode, struct file *filp)
{
#ifdef CONFIG_ZCRYPT_MULTIDEVNODES
	if (filp->f_inode->i_cdev == &zcrypt_cdev) {
		struct zcdn_device *zcdndev;

		mutex_lock(&ap_perms_mutex);
		zcdndev = find_zcdndev_by_devt(filp->f_inode->i_rdev);
		mutex_unlock(&ap_perms_mutex);
		if (zcdndev) {
			/* 2 puts here: one for find, one for open */
			put_device(&zcdndev->device);
			put_device(&zcdndev->device);
		}
	}
#endif

	atomic_dec(&zcrypt_open_count);
	return 0;
}