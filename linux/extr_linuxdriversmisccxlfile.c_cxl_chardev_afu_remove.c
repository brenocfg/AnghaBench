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
struct cxl_afu {int /*<<< orphan*/ * chardev_s; int /*<<< orphan*/  afu_cdev_s; int /*<<< orphan*/ * chardev_m; int /*<<< orphan*/  afu_cdev_m; int /*<<< orphan*/ * chardev_d; int /*<<< orphan*/  afu_cdev_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

void cxl_chardev_afu_remove(struct cxl_afu *afu)
{
	if (afu->chardev_d) {
		cdev_del(&afu->afu_cdev_d);
		device_unregister(afu->chardev_d);
		afu->chardev_d = NULL;
	}
	if (afu->chardev_m) {
		cdev_del(&afu->afu_cdev_m);
		device_unregister(afu->chardev_m);
		afu->chardev_m = NULL;
	}
	if (afu->chardev_s) {
		cdev_del(&afu->afu_cdev_s);
		device_unregister(afu->chardev_s);
		afu->chardev_s = NULL;
	}
}