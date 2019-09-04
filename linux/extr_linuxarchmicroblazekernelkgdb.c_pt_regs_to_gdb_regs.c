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
struct pvr_s {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_2__ {unsigned long* pvr; } ;

/* Variables and functions */
 size_t GDB_BTR ; 
 unsigned int GDB_PVR ; 
 size_t GDB_REDR ; 
 size_t GDB_RPID ; 
 size_t GDB_RTLBHI ; 
 size_t GDB_RTLBLO ; 
 size_t GDB_RTLBX ; 
 size_t GDB_RZPR ; 
 TYPE_1__ pvr ; 

void pt_regs_to_gdb_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	unsigned int i;
	unsigned long *pt_regb = (unsigned long *)regs;
	int temp;

	/* registers r0 - r31, pc, msr, ear, esr, fsr + do not save pt_mode */
	for (i = 0; i < (sizeof(struct pt_regs) / 4) - 1; i++)
		gdb_regs[i] = pt_regb[i];

	/* Branch target register can't be changed */
	__asm__ __volatile__ ("mfs %0, rbtr;" : "=r"(temp) : );
	gdb_regs[GDB_BTR] = temp;

	/* pvr part  - we have 11 pvr regs */
	for (i = 0; i < sizeof(struct pvr_s)/4; i++)
		gdb_regs[GDB_PVR + i] = pvr.pvr[i];

	/* read special registers - can't be changed */
	__asm__ __volatile__ ("mfs %0, redr;" : "=r"(temp) : );
	gdb_regs[GDB_REDR] = temp;
	__asm__ __volatile__ ("mfs %0, rpid;" : "=r"(temp) : );
	gdb_regs[GDB_RPID] = temp;
	__asm__ __volatile__ ("mfs %0, rzpr;" : "=r"(temp) : );
	gdb_regs[GDB_RZPR] = temp;
	__asm__ __volatile__ ("mfs %0, rtlbx;" : "=r"(temp) : );
	gdb_regs[GDB_RTLBX] = temp;
	__asm__ __volatile__ ("mfs %0, rtlblo;" : "=r"(temp) : );
	gdb_regs[GDB_RTLBLO] = temp;
	__asm__ __volatile__ ("mfs %0, rtlbhi;" : "=r"(temp) : );
	gdb_regs[GDB_RTLBHI] = temp;
}