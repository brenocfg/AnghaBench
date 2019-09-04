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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int /*<<< orphan*/  FPSCR ; 
 int /*<<< orphan*/  fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  vfp_get_float (int) ; 

__attribute__((used)) static void vfp_panic(char *reason, u32 inst)
{
	int i;

	pr_err("VFP: Error: %s\n", reason);
	pr_err("VFP: EXC 0x%08x SCR 0x%08x INST 0x%08x\n",
		fmrx(FPEXC), fmrx(FPSCR), inst);
	for (i = 0; i < 32; i += 2)
		pr_err("VFP: s%2u: 0x%08x s%2u: 0x%08x\n",
		       i, vfp_get_float(i), i+1, vfp_get_float(i+1));
}