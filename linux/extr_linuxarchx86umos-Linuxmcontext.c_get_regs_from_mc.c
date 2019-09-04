#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uml_pt_regs {int* gp; } ;
struct TYPE_3__ {int* gregs; } ;
typedef  TYPE_1__ mcontext_t ;

/* Variables and functions */
 int CS ; 
 int EFLAGS ; 
 int R10 ; 
 int R11 ; 
 int R12 ; 
 int R13 ; 
 int R14 ; 
 int R15 ; 
 int R8 ; 
 int R9 ; 
 int RAX ; 
 int RBP ; 
 int RBX ; 
 int RCX ; 
 int RDI ; 
 int RDX ; 
 size_t REG_CSGSFS ; 
 size_t REG_EFL ; 
 size_t REG_R10 ; 
 size_t REG_R11 ; 
 size_t REG_R12 ; 
 size_t REG_R13 ; 
 size_t REG_R14 ; 
 size_t REG_R15 ; 
 size_t REG_R8 ; 
 size_t REG_R9 ; 
 size_t REG_RAX ; 
 size_t REG_RBP ; 
 size_t REG_RBX ; 
 size_t REG_RCX ; 
 size_t REG_RDI ; 
 size_t REG_RDX ; 
 size_t REG_RIP ; 
 size_t REG_RSI ; 
 size_t REG_RSP ; 
 int RIP ; 
 int RSI ; 
 int RSP ; 

void get_regs_from_mc(struct uml_pt_regs *regs, mcontext_t *mc)
{
#ifdef __i386__
#define COPY2(X,Y) regs->gp[X] = mc->gregs[REG_##Y]
#define COPY(X) regs->gp[X] = mc->gregs[REG_##X]
#define COPY_SEG(X) regs->gp[X] = mc->gregs[REG_##X] & 0xffff;
#define COPY_SEG_CPL3(X) regs->gp[X] = (mc->gregs[REG_##X] & 0xffff) | 3;
	COPY_SEG(GS); COPY_SEG(FS); COPY_SEG(ES); COPY_SEG(DS);
	COPY(EDI); COPY(ESI); COPY(EBP);
	COPY2(UESP, ESP); /* sic */
	COPY(EBX); COPY(EDX); COPY(ECX); COPY(EAX);
	COPY(EIP); COPY_SEG_CPL3(CS); COPY(EFL); COPY_SEG_CPL3(SS);
#else
#define COPY2(X,Y) regs->gp[X/sizeof(unsigned long)] = mc->gregs[REG_##Y]
#define COPY(X) regs->gp[X/sizeof(unsigned long)] = mc->gregs[REG_##X]
	COPY(R8); COPY(R9); COPY(R10); COPY(R11);
	COPY(R12); COPY(R13); COPY(R14); COPY(R15);
	COPY(RDI); COPY(RSI); COPY(RBP); COPY(RBX);
	COPY(RDX); COPY(RAX); COPY(RCX); COPY(RSP);
	COPY(RIP);
	COPY2(EFLAGS, EFL);
	COPY2(CS, CSGSFS);
	regs->gp[CS / sizeof(unsigned long)] &= 0xffff;
	regs->gp[CS / sizeof(unsigned long)] |= 3;
#endif
}