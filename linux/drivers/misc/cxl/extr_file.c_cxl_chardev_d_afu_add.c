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
struct cxl_afu {int /*<<< orphan*/  chardev_d; int /*<<< orphan*/  afu_cdev_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_MKDEV_D (struct cxl_afu*) ; 
 int /*<<< orphan*/  afu_master_fops ; 
 int cxl_add_chardev (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

int cxl_chardev_d_afu_add(struct cxl_afu *afu)
{
	return cxl_add_chardev(afu, CXL_AFU_MKDEV_D(afu), &afu->afu_cdev_d,
			       &afu->chardev_d, "d", "dedicated",
			       &afu_master_fops); /* Uses master fops */
}