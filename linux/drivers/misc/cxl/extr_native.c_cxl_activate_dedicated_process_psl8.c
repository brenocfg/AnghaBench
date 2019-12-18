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
struct cxl_afu {int num_procs; int /*<<< orphan*/  current_mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AURP0_An ; 
 int /*<<< orphan*/  CXL_AURP1_An ; 
 int /*<<< orphan*/  CXL_CSRP_An ; 
 int /*<<< orphan*/  CXL_HAURP_An ; 
 int /*<<< orphan*/  CXL_MODE_DEDICATED ; 
 int /*<<< orphan*/  CXL_PSL_AMOR_An ; 
 int /*<<< orphan*/  CXL_PSL_CtxTime_An ; 
 int /*<<< orphan*/  CXL_PSL_LPID_An ; 
 int /*<<< orphan*/  CXL_PSL_SCNTL_An ; 
 int CXL_PSL_SCNTL_An_PM_Process ; 
 int /*<<< orphan*/  CXL_PSL_SDR_An ; 
 int /*<<< orphan*/  CXL_PSL_SPAP_An ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 int /*<<< orphan*/  SPRN_SDR1 ; 
 int cxl_chardev_d_afu_add (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxl_p2n_write (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int mfspr (int /*<<< orphan*/ ) ; 

int cxl_activate_dedicated_process_psl8(struct cxl_afu *afu)
{
	dev_info(&afu->dev, "Activating dedicated process mode\n");

	cxl_p1n_write(afu, CXL_PSL_SCNTL_An, CXL_PSL_SCNTL_An_PM_Process);

	cxl_p1n_write(afu, CXL_PSL_CtxTime_An, 0); /* disable */
	cxl_p1n_write(afu, CXL_PSL_SPAP_An, 0);    /* disable */
	cxl_p1n_write(afu, CXL_PSL_AMOR_An, 0xFFFFFFFFFFFFFFFFULL);
	cxl_p1n_write(afu, CXL_PSL_LPID_An, mfspr(SPRN_LPID));
	cxl_p1n_write(afu, CXL_HAURP_An, 0);       /* disable */
	cxl_p1n_write(afu, CXL_PSL_SDR_An, mfspr(SPRN_SDR1));

	cxl_p2n_write(afu, CXL_CSRP_An, 0);        /* disable */
	cxl_p2n_write(afu, CXL_AURP0_An, 0);       /* disable */
	cxl_p2n_write(afu, CXL_AURP1_An, 0);       /* disable */

	afu->current_mode = CXL_MODE_DEDICATED;
	afu->num_procs = 1;

	return cxl_chardev_d_afu_add(afu);
}