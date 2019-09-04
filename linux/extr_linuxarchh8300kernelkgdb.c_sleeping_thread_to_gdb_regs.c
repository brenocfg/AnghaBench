#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long ksp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 size_t GDB_PC ; 
 size_t GDB_SP ; 
 unsigned long KSTK_EIP (struct task_struct*) ; 
 int /*<<< orphan*/  NUMREGBYTES ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	memset((char *)gdb_regs, 0, NUMREGBYTES);
	gdb_regs[GDB_SP] = p->thread.ksp;
	gdb_regs[GDB_PC] = KSTK_EIP(p);
}