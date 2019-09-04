#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct callee_regs {int dummy; } ;
struct TYPE_3__ {scalar_t__ callee_reg; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  to_gdb_regs (unsigned long*,struct pt_regs*,struct callee_regs*) ; 

void pt_regs_to_gdb_regs(unsigned long *gdb_regs, struct pt_regs *kernel_regs)
{
	to_gdb_regs(gdb_regs, kernel_regs, (struct callee_regs *)
		current->thread.callee_reg);
}