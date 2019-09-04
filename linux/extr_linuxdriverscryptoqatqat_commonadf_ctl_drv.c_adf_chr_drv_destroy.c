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
struct TYPE_2__ {int /*<<< orphan*/  major; int /*<<< orphan*/  drv_class; int /*<<< orphan*/  drv_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ adf_ctl_drv ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adf_chr_drv_destroy(void)
{
	device_destroy(adf_ctl_drv.drv_class, MKDEV(adf_ctl_drv.major, 0));
	cdev_del(&adf_ctl_drv.drv_cdev);
	class_destroy(adf_ctl_drv.drv_class);
	unregister_chrdev_region(MKDEV(adf_ctl_drv.major, 0), 1);
}