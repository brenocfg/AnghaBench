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
struct switch_stack {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_EA ; 
 int /*<<< orphan*/  PT_ESTATUS ; 
 int /*<<< orphan*/  PT_FP ; 
 int /*<<< orphan*/  PT_GP ; 
 int /*<<< orphan*/  PT_ORIG_R2 ; 
 int /*<<< orphan*/  PT_ORIG_R7 ; 
 int /*<<< orphan*/  PT_R1 ; 
 int /*<<< orphan*/  PT_R10 ; 
 int /*<<< orphan*/  PT_R11 ; 
 int /*<<< orphan*/  PT_R12 ; 
 int /*<<< orphan*/  PT_R13 ; 
 int /*<<< orphan*/  PT_R14 ; 
 int /*<<< orphan*/  PT_R15 ; 
 int /*<<< orphan*/  PT_R2 ; 
 int /*<<< orphan*/  PT_R3 ; 
 int /*<<< orphan*/  PT_R4 ; 
 int /*<<< orphan*/  PT_R5 ; 
 int /*<<< orphan*/  PT_R6 ; 
 int /*<<< orphan*/  PT_R7 ; 
 int /*<<< orphan*/  PT_R8 ; 
 int /*<<< orphan*/  PT_R9 ; 
 int /*<<< orphan*/  PT_RA ; 
 int /*<<< orphan*/  PT_REGS_SIZE ; 
 int /*<<< orphan*/  PT_SP ; 
 int /*<<< orphan*/  SWITCH_STACK_SIZE ; 
 int /*<<< orphan*/  SW_FP ; 
 int /*<<< orphan*/  SW_GP ; 
 int /*<<< orphan*/  SW_R16 ; 
 int /*<<< orphan*/  SW_R17 ; 
 int /*<<< orphan*/  SW_R18 ; 
 int /*<<< orphan*/  SW_R19 ; 
 int /*<<< orphan*/  SW_R20 ; 
 int /*<<< orphan*/  SW_R21 ; 
 int /*<<< orphan*/  SW_R22 ; 
 int /*<<< orphan*/  SW_R23 ; 
 int /*<<< orphan*/  SW_RA ; 
 int /*<<< orphan*/  TASK_THREAD ; 
 int /*<<< orphan*/  THREAD_KPSR ; 
 int /*<<< orphan*/  THREAD_KSP ; 
 int /*<<< orphan*/  TI_FLAGS ; 
 int /*<<< orphan*/  TI_PREEMPT_COUNT ; 
 int /*<<< orphan*/  ea ; 
 int /*<<< orphan*/  estatus ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  fp ; 
 int /*<<< orphan*/  gp ; 
 int /*<<< orphan*/  kpsr ; 
 int /*<<< orphan*/  ksp ; 
 int /*<<< orphan*/  orig_r2 ; 
 int /*<<< orphan*/  orig_r7 ; 
 int /*<<< orphan*/  preempt_count ; 
 int /*<<< orphan*/  pt_regs ; 
 int /*<<< orphan*/  r1 ; 
 int /*<<< orphan*/  r10 ; 
 int /*<<< orphan*/  r11 ; 
 int /*<<< orphan*/  r12 ; 
 int /*<<< orphan*/  r13 ; 
 int /*<<< orphan*/  r14 ; 
 int /*<<< orphan*/  r15 ; 
 int /*<<< orphan*/  r16 ; 
 int /*<<< orphan*/  r17 ; 
 int /*<<< orphan*/  r18 ; 
 int /*<<< orphan*/  r19 ; 
 int /*<<< orphan*/  r2 ; 
 int /*<<< orphan*/  r20 ; 
 int /*<<< orphan*/  r21 ; 
 int /*<<< orphan*/  r22 ; 
 int /*<<< orphan*/  r23 ; 
 int /*<<< orphan*/  r3 ; 
 int /*<<< orphan*/  r4 ; 
 int /*<<< orphan*/  r5 ; 
 int /*<<< orphan*/  r6 ; 
 int /*<<< orphan*/  r7 ; 
 int /*<<< orphan*/  r8 ; 
 int /*<<< orphan*/  r9 ; 
 int /*<<< orphan*/  ra ; 
 int /*<<< orphan*/  sp ; 
 int /*<<< orphan*/  switch_stack ; 
 int /*<<< orphan*/  task_struct ; 
 int /*<<< orphan*/  thread ; 
 int /*<<< orphan*/  thread_info ; 
 int /*<<< orphan*/  thread_struct ; 

int main(void)
{
	/* struct task_struct */
	OFFSET(TASK_THREAD, task_struct, thread);
	BLANK();

	/* struct thread_struct */
	OFFSET(THREAD_KSP, thread_struct, ksp);
	OFFSET(THREAD_KPSR, thread_struct, kpsr);
	BLANK();

	/* struct pt_regs */
	OFFSET(PT_ORIG_R2, pt_regs, orig_r2);
	OFFSET(PT_ORIG_R7, pt_regs, orig_r7);

	OFFSET(PT_R1, pt_regs, r1);
	OFFSET(PT_R2, pt_regs, r2);
	OFFSET(PT_R3, pt_regs, r3);
	OFFSET(PT_R4, pt_regs, r4);
	OFFSET(PT_R5, pt_regs, r5);
	OFFSET(PT_R6, pt_regs, r6);
	OFFSET(PT_R7, pt_regs, r7);
	OFFSET(PT_R8, pt_regs, r8);
	OFFSET(PT_R9, pt_regs, r9);
	OFFSET(PT_R10, pt_regs, r10);
	OFFSET(PT_R11, pt_regs, r11);
	OFFSET(PT_R12, pt_regs, r12);
	OFFSET(PT_R13, pt_regs, r13);
	OFFSET(PT_R14, pt_regs, r14);
	OFFSET(PT_R15, pt_regs, r15);
	OFFSET(PT_EA, pt_regs, ea);
	OFFSET(PT_RA, pt_regs, ra);
	OFFSET(PT_FP, pt_regs, fp);
	OFFSET(PT_SP, pt_regs, sp);
	OFFSET(PT_GP, pt_regs, gp);
	OFFSET(PT_ESTATUS, pt_regs, estatus);
	DEFINE(PT_REGS_SIZE, sizeof(struct pt_regs));
	BLANK();

	/* struct switch_stack */
	OFFSET(SW_R16, switch_stack, r16);
	OFFSET(SW_R17, switch_stack, r17);
	OFFSET(SW_R18, switch_stack, r18);
	OFFSET(SW_R19, switch_stack, r19);
	OFFSET(SW_R20, switch_stack, r20);
	OFFSET(SW_R21, switch_stack, r21);
	OFFSET(SW_R22, switch_stack, r22);
	OFFSET(SW_R23, switch_stack, r23);
	OFFSET(SW_FP, switch_stack, fp);
	OFFSET(SW_GP, switch_stack, gp);
	OFFSET(SW_RA, switch_stack, ra);
	DEFINE(SWITCH_STACK_SIZE, sizeof(struct switch_stack));
	BLANK();

	/* struct thread_info */
	OFFSET(TI_FLAGS, thread_info, flags);
	OFFSET(TI_PREEMPT_COUNT, thread_info, preempt_count);
	BLANK();

	return 0;
}