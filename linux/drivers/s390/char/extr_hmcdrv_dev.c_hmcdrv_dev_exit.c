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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ hmcdrv_dev ; 
 int /*<<< orphan*/  hmcdrv_dev_class ; 
 int /*<<< orphan*/  hmcdrv_dev_no ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

void hmcdrv_dev_exit(void)
{
#ifdef HMCDRV_DEV_CLASS
	if (!IS_ERR_OR_NULL(hmcdrv_dev_class)) {
		device_destroy(hmcdrv_dev_class, hmcdrv_dev_no);
		class_destroy(hmcdrv_dev_class);
	}

	cdev_del(&hmcdrv_dev.dev);
	unregister_chrdev_region(hmcdrv_dev_no, 1);
#else  /* !HMCDRV_DEV_CLASS */
	misc_deregister(&hmcdrv_dev.dev);
#endif	/* HMCDRV_DEV_CLASS */
}