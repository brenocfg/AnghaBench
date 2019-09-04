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
typedef  int /*<<< orphan*/  u64 ;
struct cxl_afu {scalar_t__ current_mode; } ;

/* Variables and functions */
 int CXL_AFU_Cntl_An_ES_Disabled ; 
 int CXL_AFU_Cntl_An_ES_MASK ; 
 int /*<<< orphan*/  CXL_AFU_Cntl_An_RA ; 
 int CXL_AFU_Cntl_An_RS_Complete ; 
 int CXL_AFU_Cntl_An_RS_MASK ; 
 int /*<<< orphan*/  CXL_PSL_SERR_An ; 
 int /*<<< orphan*/  CXL_PSL_SERR_An_IRQ_MASKS ; 
 int afu_control (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cxl_p1n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 

__attribute__((used)) static int native_afu_reset(struct cxl_afu *afu)
{
	int rc;
	u64 serr;

	pr_devel("AFU reset request\n");

	rc = afu_control(afu, CXL_AFU_Cntl_An_RA, 0,
			   CXL_AFU_Cntl_An_RS_Complete | CXL_AFU_Cntl_An_ES_Disabled,
			   CXL_AFU_Cntl_An_RS_MASK | CXL_AFU_Cntl_An_ES_MASK,
			   false);

	/*
	 * Re-enable any masked interrupts when the AFU is not
	 * activated to avoid side effects after attaching a process
	 * in dedicated mode.
	 */
	if (afu->current_mode == 0) {
		serr = cxl_p1n_read(afu, CXL_PSL_SERR_An);
		serr &= ~CXL_PSL_SERR_An_IRQ_MASKS;
		cxl_p1n_write(afu, CXL_PSL_SERR_An, serr);
	}

	return rc;
}