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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {unsigned long sp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct inactive_task_frame {unsigned long bp; } ;

/* Variables and functions */
 size_t GDB_AX ; 
 size_t GDB_BP ; 
 size_t GDB_BX ; 
 size_t GDB_CS ; 
 size_t GDB_CX ; 
 size_t GDB_DI ; 
 size_t GDB_DX ; 
 size_t GDB_PC ; 
 size_t GDB_PS ; 
 size_t GDB_R10 ; 
 size_t GDB_R11 ; 
 size_t GDB_R12 ; 
 size_t GDB_R13 ; 
 size_t GDB_R14 ; 
 size_t GDB_R15 ; 
 size_t GDB_R8 ; 
 size_t GDB_R9 ; 
 size_t GDB_SI ; 
 size_t GDB_SP ; 
 size_t GDB_SS ; 
 scalar_t__ __KERNEL_CS ; 
 scalar_t__ __KERNEL_DS ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
#ifndef CONFIG_X86_32
	u32 *gdb_regs32 = (u32 *)gdb_regs;
#endif
	gdb_regs[GDB_AX]	= 0;
	gdb_regs[GDB_BX]	= 0;
	gdb_regs[GDB_CX]	= 0;
	gdb_regs[GDB_DX]	= 0;
	gdb_regs[GDB_SI]	= 0;
	gdb_regs[GDB_DI]	= 0;
	gdb_regs[GDB_BP]	= ((struct inactive_task_frame *)p->thread.sp)->bp;
#ifdef CONFIG_X86_32
	gdb_regs[GDB_DS]	= __KERNEL_DS;
	gdb_regs[GDB_ES]	= __KERNEL_DS;
	gdb_regs[GDB_PS]	= 0;
	gdb_regs[GDB_CS]	= __KERNEL_CS;
	gdb_regs[GDB_SS]	= __KERNEL_DS;
	gdb_regs[GDB_FS]	= 0xFFFF;
	gdb_regs[GDB_GS]	= 0xFFFF;
#else
	gdb_regs32[GDB_PS]	= 0;
	gdb_regs32[GDB_CS]	= __KERNEL_CS;
	gdb_regs32[GDB_SS]	= __KERNEL_DS;
	gdb_regs[GDB_R8]	= 0;
	gdb_regs[GDB_R9]	= 0;
	gdb_regs[GDB_R10]	= 0;
	gdb_regs[GDB_R11]	= 0;
	gdb_regs[GDB_R12]	= 0;
	gdb_regs[GDB_R13]	= 0;
	gdb_regs[GDB_R14]	= 0;
	gdb_regs[GDB_R15]	= 0;
#endif
	gdb_regs[GDB_PC]	= 0;
	gdb_regs[GDB_SP]	= p->thread.sp;
}