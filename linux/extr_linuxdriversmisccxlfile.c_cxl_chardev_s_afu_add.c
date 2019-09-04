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
struct cxl_afu {int /*<<< orphan*/  chardev_s; int /*<<< orphan*/  afu_cdev_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_MKDEV_S (struct cxl_afu*) ; 
 int /*<<< orphan*/  afu_fops ; 
 int cxl_add_chardev (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

int cxl_chardev_s_afu_add(struct cxl_afu *afu)
{
	return cxl_add_chardev(afu, CXL_AFU_MKDEV_S(afu), &afu->afu_cdev_s,
			       &afu->chardev_s, "s", "shared",
			       &afu_fops);
}