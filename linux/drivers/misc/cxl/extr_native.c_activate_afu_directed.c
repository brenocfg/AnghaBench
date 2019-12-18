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
struct cxl_afu {int /*<<< orphan*/  current_mode; TYPE_1__* native; int /*<<< orphan*/  max_procs_virtualised; int /*<<< orphan*/  num_procs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_MODE_DIRECTED ; 
 int /*<<< orphan*/  CXL_PSL_AMOR_An ; 
 int /*<<< orphan*/  CXL_PSL_ID_An ; 
 int CXL_PSL_ID_An_F ; 
 int CXL_PSL_ID_An_L ; 
 int /*<<< orphan*/  CXL_PSL_SCNTL_An ; 
 int CXL_PSL_SCNTL_An_PM_AFU ; 
 int ENOMEM ; 
 int /*<<< orphan*/  attach_spa (struct cxl_afu*) ; 
 scalar_t__ cxl_alloc_spa (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_chardev_afu_remove (struct cxl_afu*) ; 
 int cxl_chardev_m_afu_add (struct cxl_afu*) ; 
 int cxl_chardev_s_afu_add (struct cxl_afu*) ; 
 scalar_t__ cxl_is_power8 () ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int cxl_sysfs_afu_m_add (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_sysfs_afu_m_remove (struct cxl_afu*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int activate_afu_directed(struct cxl_afu *afu)
{
	int rc;

	dev_info(&afu->dev, "Activating AFU directed mode\n");

	afu->num_procs = afu->max_procs_virtualised;
	if (afu->native->spa == NULL) {
		if (cxl_alloc_spa(afu, CXL_MODE_DIRECTED))
			return -ENOMEM;
	}
	attach_spa(afu);

	cxl_p1n_write(afu, CXL_PSL_SCNTL_An, CXL_PSL_SCNTL_An_PM_AFU);
	if (cxl_is_power8())
		cxl_p1n_write(afu, CXL_PSL_AMOR_An, 0xFFFFFFFFFFFFFFFFULL);
	cxl_p1n_write(afu, CXL_PSL_ID_An, CXL_PSL_ID_An_F | CXL_PSL_ID_An_L);

	afu->current_mode = CXL_MODE_DIRECTED;

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