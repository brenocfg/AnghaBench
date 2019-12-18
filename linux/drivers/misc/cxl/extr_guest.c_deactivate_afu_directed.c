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
struct cxl_afu {scalar_t__ num_procs; scalar_t__ current_mode; int /*<<< orphan*/  slice; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* afu_reset ) (struct cxl_afu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_chardev_afu_remove (struct cxl_afu*) ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  cxl_sysfs_afu_m_remove (struct cxl_afu*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cxl_afu*) ; 

__attribute__((used)) static int deactivate_afu_directed(struct cxl_afu *afu)
{
	dev_info(&afu->dev, "Deactivating AFU(%d) directed mode\n", afu->slice);

	afu->current_mode = 0;
	afu->num_procs = 0;

	cxl_sysfs_afu_m_remove(afu);
	cxl_chardev_afu_remove(afu);

	cxl_ops->afu_reset(afu);

	return 0;
}