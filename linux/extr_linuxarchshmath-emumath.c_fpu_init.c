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
struct sh_fpu_soft_struct {scalar_t__* xfp_regs; scalar_t__* fp_regs; scalar_t__ fpul; int /*<<< orphan*/  fpscr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_INIT ; 

__attribute__((used)) static void fpu_init(struct sh_fpu_soft_struct *fpu)
{
	int i;

	fpu->fpscr = FPSCR_INIT;
	fpu->fpul = 0;

	for (i = 0; i < 16; i++) {
		fpu->fp_regs[i] = 0;
		fpu->xfp_regs[i]= 0;
	}
}