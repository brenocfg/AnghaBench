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
struct sh_fpu_soft_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMOV_EXT (int) ; 
 scalar_t__ FPSCR_SZ ; 
 int /*<<< orphan*/  FRm ; 
 scalar_t__ R0 ; 
 scalar_t__ Rn ; 
 int /*<<< orphan*/  WRITE (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
fmov_reg_idx(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(m);
		WRITE(FRm, Rn + R0 + 4);
		m++;
		WRITE(FRm, Rn + R0);
	} else {
		WRITE(FRm, Rn + R0);
	}

	return 0;
}