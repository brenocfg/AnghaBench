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
struct vme_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  resource; int /*<<< orphan*/  pci_buf; int /*<<< orphan*/  kern_buf; int /*<<< orphan*/  size_buf; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int MASTER_MAX ; 
 int MASTER_MINOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int SLAVE_MAX ; 
 int SLAVE_MINOR ; 
 int /*<<< orphan*/  VME_A32 ; 
 int VME_DEVS ; 
 int /*<<< orphan*/  VME_MAJOR ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* image ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vme_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vme_master_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vme_slave_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vme_slave_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vme_user_cdev ; 
 int /*<<< orphan*/  vme_user_sysfs_class ; 

__attribute__((used)) static int vme_user_remove(struct vme_dev *dev)
{
	int i;

	/* Remove sysfs Entries */
	for (i = 0; i < VME_DEVS; i++) {
		mutex_destroy(&image[i].mutex);
		device_destroy(vme_user_sysfs_class, MKDEV(VME_MAJOR, i));
	}
	class_destroy(vme_user_sysfs_class);

	for (i = MASTER_MINOR; i < (MASTER_MAX + 1); i++) {
		kfree(image[i].kern_buf);
		vme_master_free(image[i].resource);
	}

	for (i = SLAVE_MINOR; i < (SLAVE_MAX + 1); i++) {
		vme_slave_set(image[i].resource, 0, 0, 0, 0, VME_A32, 0);
		vme_free_consistent(image[i].resource, image[i].size_buf,
				    image[i].kern_buf, image[i].pci_buf);
		vme_slave_free(image[i].resource);
	}

	/* Unregister device driver */
	cdev_del(vme_user_cdev);

	/* Unregister the major and minor device numbers */
	unregister_chrdev_region(MKDEV(VME_MAJOR, 0), VME_DEVS);

	return 0;
}