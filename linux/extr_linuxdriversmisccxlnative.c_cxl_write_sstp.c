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
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_SSTP0_An ; 
 int /*<<< orphan*/  CXL_SSTP1_An ; 
 int cxl_afu_slbia (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_p2n_write (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxl_write_sstp(struct cxl_afu *afu, u64 sstp0, u64 sstp1)
{
	int rc;

	/* 1. Disable SSTP by writing 0 to SSTP1[V] */
	cxl_p2n_write(afu, CXL_SSTP1_An, 0);

	/* 2. Invalidate all SLB entries */
	if ((rc = cxl_afu_slbia(afu)))
		return rc;

	/* 3. Set SSTP0_An */
	cxl_p2n_write(afu, CXL_SSTP0_An, sstp0);

	/* 4. Set SSTP1_An */
	cxl_p2n_write(afu, CXL_SSTP1_An, sstp1);

	return 0;
}