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
struct cosm_device {int /*<<< orphan*/  bootmode; int /*<<< orphan*/  ramdisk; int /*<<< orphan*/  firmware; int /*<<< orphan*/  cmdline; int /*<<< orphan*/  reset_trigger_work; int /*<<< orphan*/  index; int /*<<< orphan*/  state_sysfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cosm_delete_debug_dir (struct cosm_device*) ; 
 int /*<<< orphan*/  cosm_scif_exit () ; 
 int /*<<< orphan*/  cosm_stop (struct cosm_device*,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_cosm_class ; 
 int /*<<< orphan*/  g_num_dev ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cosm_driver_remove(struct cosm_device *cdev)
{
	cosm_delete_debug_dir(cdev);
	sysfs_put(cdev->state_sysfs);
	device_destroy(g_cosm_class, MKDEV(0, cdev->index));
	flush_work(&cdev->reset_trigger_work);
	cosm_stop(cdev, false);
	if (atomic_dec_and_test(&g_num_dev))
		cosm_scif_exit();

	/* These sysfs entries might have allocated */
	kfree(cdev->cmdline);
	kfree(cdev->firmware);
	kfree(cdev->ramdisk);
	kfree(cdev->bootmode);
}