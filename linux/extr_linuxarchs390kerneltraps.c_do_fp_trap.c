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
struct pt_regs {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int FPE_FLTDIV ; 
 int FPE_FLTINV ; 
 int FPE_FLTOVF ; 
 int FPE_FLTRES ; 
 int FPE_FLTUND ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  do_trap (struct pt_regs*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static inline void do_fp_trap(struct pt_regs *regs, __u32 fpc)
{
	int si_code = 0;
	/* FPC[2] is Data Exception Code */
	if ((fpc & 0x00000300) == 0) {
		/* bits 6 and 7 of DXC are 0 iff IEEE exception */
		if (fpc & 0x8000) /* invalid fp operation */
			si_code = FPE_FLTINV;
		else if (fpc & 0x4000) /* div by 0 */
			si_code = FPE_FLTDIV;
		else if (fpc & 0x2000) /* overflow */
			si_code = FPE_FLTOVF;
		else if (fpc & 0x1000) /* underflow */
			si_code = FPE_FLTUND;
		else if (fpc & 0x0800) /* inexact */
			si_code = FPE_FLTRES;
	}
	do_trap(regs, SIGFPE, si_code, "floating point exception");
}