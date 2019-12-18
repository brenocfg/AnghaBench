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
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_APCALLOC_A ; 
 int /*<<< orphan*/  CXL_PSL_COALLOC_A ; 
 int /*<<< orphan*/  CXL_PSL_RXCTL_A ; 
 int CXL_PSL_RXCTL_AFUHP_4S ; 
 int /*<<< orphan*/  CXL_PSL_SLICE_TRACE ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_implementation_afu_regs_psl8(struct cxl_afu *afu)
{
	/* read/write masks for this slice */
	cxl_p1n_write(afu, CXL_PSL_APCALLOC_A, 0xFFFFFFFEFEFEFEFEULL);
	/* APC read/write masks for this slice */
	cxl_p1n_write(afu, CXL_PSL_COALLOC_A, 0xFF000000FEFEFEFEULL);
	/* for debugging with trace arrays */
	cxl_p1n_write(afu, CXL_PSL_SLICE_TRACE, 0x0000FFFF00000000ULL);
	cxl_p1n_write(afu, CXL_PSL_RXCTL_A, CXL_PSL_RXCTL_AFUHP_4S);

	return 0;
}