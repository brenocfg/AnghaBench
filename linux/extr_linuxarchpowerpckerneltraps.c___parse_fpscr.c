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

/* Variables and functions */
 int FPE_FLTDIV ; 
 int FPE_FLTINV ; 
 int FPE_FLTOVF ; 
 int FPE_FLTRES ; 
 int FPE_FLTUND ; 
 int FPE_FLTUNK ; 
 unsigned long FPSCR_OE ; 
 unsigned long FPSCR_OX ; 
 unsigned long FPSCR_UE ; 
 unsigned long FPSCR_UX ; 
 unsigned long FPSCR_VE ; 
 unsigned long FPSCR_VX ; 
 unsigned long FPSCR_XE ; 
 unsigned long FPSCR_XX ; 
 unsigned long FPSCR_ZE ; 
 unsigned long FPSCR_ZX ; 

__attribute__((used)) static inline int __parse_fpscr(unsigned long fpscr)
{
	int ret = FPE_FLTUNK;

	/* Invalid operation */
	if ((fpscr & FPSCR_VE) && (fpscr & FPSCR_VX))
		ret = FPE_FLTINV;

	/* Overflow */
	else if ((fpscr & FPSCR_OE) && (fpscr & FPSCR_OX))
		ret = FPE_FLTOVF;

	/* Underflow */
	else if ((fpscr & FPSCR_UE) && (fpscr & FPSCR_UX))
		ret = FPE_FLTUND;

	/* Divide by zero */
	else if ((fpscr & FPSCR_ZE) && (fpscr & FPSCR_ZX))
		ret = FPE_FLTDIV;

	/* Inexact result */
	else if ((fpscr & FPSCR_XE) && (fpscr & FPSCR_XX))
		ret = FPE_FLTRES;

	return ret;
}