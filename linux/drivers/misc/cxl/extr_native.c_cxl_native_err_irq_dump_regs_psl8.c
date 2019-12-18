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
struct cxl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_FIR1 ; 
 int /*<<< orphan*/  CXL_PSL_FIR2 ; 
 int /*<<< orphan*/  cxl_p1_read (struct cxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cxl_native_err_irq_dump_regs_psl8(struct cxl *adapter)
{
	u64 fir1, fir2;

	fir1 = cxl_p1_read(adapter, CXL_PSL_FIR1);
	fir2 = cxl_p1_read(adapter, CXL_PSL_FIR2);
	dev_crit(&adapter->dev,
		 "PSL_FIR1: 0x%016llx\nPSL_FIR2: 0x%016llx\n",
		 fir1, fir2);
}