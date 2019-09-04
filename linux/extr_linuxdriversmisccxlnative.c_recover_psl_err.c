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
typedef  int u64 ;
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_DSISR_An ; 
 int CXL_PSL_DSISR_An_PE ; 
 int /*<<< orphan*/  CXL_PSL_ErrStat_An ; 
 int cxl_p2n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p2n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_devel (char*,int) ; 

__attribute__((used)) static void recover_psl_err(struct cxl_afu *afu, u64 errstat)
{
	u64 dsisr;

	pr_devel("RECOVERING FROM PSL ERROR... (0x%016llx)\n", errstat);

	/* Clear PSL_DSISR[PE] */
	dsisr = cxl_p2n_read(afu, CXL_PSL_DSISR_An);
	cxl_p2n_write(afu, CXL_PSL_DSISR_An, dsisr & ~CXL_PSL_DSISR_An_PE);

	/* Write 1s to clear error status bits */
	cxl_p2n_write(afu, CXL_PSL_ErrStat_An, errstat);
}