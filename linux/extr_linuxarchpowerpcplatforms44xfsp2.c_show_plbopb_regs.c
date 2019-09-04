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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ PLB4OPB_GEAR ; 
 scalar_t__ PLB4OPB_GEARU ; 
 scalar_t__ PLB4OPB_GESR0 ; 
 scalar_t__ PLB4OPB_GESR1 ; 
 scalar_t__ PLB4OPB_GESR2 ; 
 int mfdcr (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void show_plbopb_regs(u32 base, int num)
{
	pr_err("\nPLBOPB Bridge %d:\n", num);
	pr_err("GESR0: 0x%08x\n", mfdcr(base + PLB4OPB_GESR0));
	pr_err("GESR1: 0x%08x\n", mfdcr(base + PLB4OPB_GESR1));
	pr_err("GESR2: 0x%08x\n", mfdcr(base + PLB4OPB_GESR2));
	pr_err("GEARU: 0x%08x\n", mfdcr(base + PLB4OPB_GEARU));
	pr_err("GEAR:  0x%08x\n", mfdcr(base + PLB4OPB_GEAR));
}