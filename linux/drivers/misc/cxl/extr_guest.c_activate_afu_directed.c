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
struct cxl_afu {int /*<<< orphan*/  max_procs_virtualised; int /*<<< orphan*/  num_procs; int /*<<< orphan*/  current_mode; int /*<<< orphan*/  slice; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_MODE_DIRECTED ; 
 int /*<<< orphan*/  cxl_chardev_afu_remove (struct cxl_afu*) ; 
 int cxl_chardev_m_afu_add (struct cxl_afu*) ; 
 int cxl_chardev_s_afu_add (struct cxl_afu*) ; 
 int cxl_sysfs_afu_m_add (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_sysfs_afu_m_remove (struct cxl_afu*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int activate_afu_directed(struct cxl_afu *afu)
{
	int rc;

	dev_info(&afu->dev, "Activating AFU(%d) directed mode\n", afu->slice);

	afu->current_mode = CXL_MODE_DIRECTED;

	afu->num_procs = afu->max_procs_virtualised;

	if ((rc = cxl_chardev_m_afu_add(afu)))
		return rc;

	if ((rc = cxl_sysfs_afu_m_add(afu)))
		goto err;

	if ((rc = cxl_chardev_s_afu_add(afu)))
		goto err1;

	return 0;
err1:
	cxl_sysfs_afu_m_remove(afu);
err:
	cxl_chardev_afu_remove(afu);
	return rc;
}