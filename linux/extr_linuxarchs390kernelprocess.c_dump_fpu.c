#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  fprs; scalar_t__ pad; int /*<<< orphan*/  fpc; } ;
typedef  TYPE_3__ s390_fp_regs ;
typedef  int /*<<< orphan*/  freg_t ;
struct TYPE_6__ {int /*<<< orphan*/  fprs; int /*<<< orphan*/  vxrs; int /*<<< orphan*/  fpc; } ;
struct TYPE_7__ {TYPE_1__ fpu; } ;
struct TYPE_9__ {TYPE_2__ thread; } ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_VX ; 
 int /*<<< orphan*/  convert_vx_to_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_fpu_regs () ; 

int dump_fpu (struct pt_regs * regs, s390_fp_regs *fpregs)
{
	save_fpu_regs();
	fpregs->fpc = current->thread.fpu.fpc;
	fpregs->pad = 0;
	if (MACHINE_HAS_VX)
		convert_vx_to_fp((freg_t *)&fpregs->fprs,
				 current->thread.fpu.vxrs);
	else
		memcpy(&fpregs->fprs, current->thread.fpu.fprs,
		       sizeof(fpregs->fprs));
	return 1;
}