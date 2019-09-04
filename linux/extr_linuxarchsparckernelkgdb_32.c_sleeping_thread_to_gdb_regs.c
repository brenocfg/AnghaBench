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
struct thread_info {unsigned long ksp; unsigned long kpsr; unsigned long kwim; unsigned long kpc; } ;
struct task_struct {int dummy; } ;
struct reg_window32 {unsigned long* locals; unsigned long* ins; } ;

/* Variables and functions */
 size_t GDB_CSR ; 
 int GDB_F0 ; 
 int GDB_F31 ; 
 size_t GDB_FSR ; 
 int GDB_G0 ; 
 int GDB_G6 ; 
 size_t GDB_G7 ; 
 int GDB_I0 ; 
 int GDB_L0 ; 
 size_t GDB_NPC ; 
 int GDB_O0 ; 
 size_t GDB_O7 ; 
 size_t GDB_PC ; 
 size_t GDB_PSR ; 
 int GDB_SP ; 
 size_t GDB_TBR ; 
 size_t GDB_WIM ; 
 size_t GDB_Y ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  trapbase ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	struct thread_info *t = task_thread_info(p);
	struct reg_window32 *win;
	int i;

	for (i = GDB_G0; i < GDB_G6; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_G6] = (unsigned long) t;
	gdb_regs[GDB_G7] = 0;
	for (i = GDB_O0; i < GDB_SP; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_SP] = t->ksp;
	gdb_regs[GDB_O7] = 0;

	win = (struct reg_window32 *) t->ksp;
	for (i = 0; i < 8; i++)
		gdb_regs[GDB_L0 + i] = win->locals[i];
	for (i = 0; i < 8; i++)
		gdb_regs[GDB_I0 + i] = win->ins[i];

	for (i = GDB_F0; i <= GDB_F31; i++)
		gdb_regs[i] = 0;

	gdb_regs[GDB_Y] = 0;

	gdb_regs[GDB_PSR] = t->kpsr;
	gdb_regs[GDB_WIM] = t->kwim;
	gdb_regs[GDB_TBR] = (unsigned long) &trapbase;
	gdb_regs[GDB_PC] = t->kpc;
	gdb_regs[GDB_NPC] = t->kpc + 4;
	gdb_regs[GDB_FSR] = 0;
	gdb_regs[GDB_CSR] = 0;
}