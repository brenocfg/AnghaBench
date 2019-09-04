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
struct reg_window32 {unsigned long* locals; unsigned long* ins; } ;
struct pt_regs {unsigned long* u_regs; unsigned long y; unsigned long psr; unsigned long pc; unsigned long npc; } ;

/* Variables and functions */
 size_t GDB_CSR ; 
 int GDB_F0 ; 
 int GDB_F31 ; 
 size_t GDB_FSR ; 
 size_t GDB_G0 ; 
 int GDB_G1 ; 
 int GDB_I0 ; 
 int GDB_L0 ; 
 size_t GDB_NPC ; 
 size_t GDB_PC ; 
 size_t GDB_PSR ; 
 size_t GDB_TBR ; 
 size_t GDB_WIM ; 
 size_t GDB_Y ; 
 size_t UREG_FP ; 
 int UREG_G1 ; 
 int /*<<< orphan*/  trapbase ; 

void pt_regs_to_gdb_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	struct reg_window32 *win;
	int i;

	gdb_regs[GDB_G0] = 0;
	for (i = 0; i < 15; i++)
		gdb_regs[GDB_G1 + i] = regs->u_regs[UREG_G1 + i];

	win = (struct reg_window32 *) regs->u_regs[UREG_FP];
	for (i = 0; i < 8; i++)
		gdb_regs[GDB_L0 + i] = win->locals[i];
	for (i = 0; i < 8; i++)
		gdb_regs[GDB_I0 + i] = win->ins[i];

	for (i = GDB_F0; i <= GDB_F31; i++)
		gdb_regs[i] = 0;

	gdb_regs[GDB_Y] = regs->y;
	gdb_regs[GDB_PSR] = regs->psr;
	gdb_regs[GDB_WIM] = 0;
	gdb_regs[GDB_TBR] = (unsigned long) &trapbase;
	gdb_regs[GDB_PC] = regs->pc;
	gdb_regs[GDB_NPC] = regs->npc;
	gdb_regs[GDB_FSR] = 0;
	gdb_regs[GDB_CSR] = 0;
}