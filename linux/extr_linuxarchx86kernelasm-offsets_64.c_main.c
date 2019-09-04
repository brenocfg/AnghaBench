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
typedef  int /*<<< orphan*/  syscalls_ia32 ;
typedef  int /*<<< orphan*/  syscalls_64 ;
struct TYPE_2__ {int /*<<< orphan*/  ist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IA32_NR_syscalls ; 
 int /*<<< orphan*/  NR_syscalls ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSS_ist ; 
 int /*<<< orphan*/  __NR_syscall_compat_max ; 
 int /*<<< orphan*/  __NR_syscall_max ; 
 int /*<<< orphan*/  bp ; 
 int /*<<< orphan*/  bx ; 
 int /*<<< orphan*/  cr0 ; 
 int /*<<< orphan*/  cr2 ; 
 int /*<<< orphan*/  cr3 ; 
 int /*<<< orphan*/  cr4 ; 
 int /*<<< orphan*/  cr8 ; 
 int /*<<< orphan*/  cx ; 
 int /*<<< orphan*/  di ; 
 int /*<<< orphan*/  dx ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  gdt_desc ; 
 int /*<<< orphan*/  pt_regs ; 
 int /*<<< orphan*/  pt_regs_bp ; 
 int /*<<< orphan*/  pt_regs_bx ; 
 int /*<<< orphan*/  pt_regs_cx ; 
 int /*<<< orphan*/  pt_regs_di ; 
 int /*<<< orphan*/  pt_regs_dx ; 
 int /*<<< orphan*/  pt_regs_flags ; 
 int /*<<< orphan*/  pt_regs_r10 ; 
 int /*<<< orphan*/  pt_regs_r11 ; 
 int /*<<< orphan*/  pt_regs_r12 ; 
 int /*<<< orphan*/  pt_regs_r13 ; 
 int /*<<< orphan*/  pt_regs_r14 ; 
 int /*<<< orphan*/  pt_regs_r15 ; 
 int /*<<< orphan*/  pt_regs_r8 ; 
 int /*<<< orphan*/  pt_regs_r9 ; 
 int /*<<< orphan*/  pt_regs_si ; 
 int /*<<< orphan*/  pt_regs_sp ; 
 int /*<<< orphan*/  r10 ; 
 int /*<<< orphan*/  r11 ; 
 int /*<<< orphan*/  r12 ; 
 int /*<<< orphan*/  r13 ; 
 int /*<<< orphan*/  r14 ; 
 int /*<<< orphan*/  r15 ; 
 int /*<<< orphan*/  r8 ; 
 int /*<<< orphan*/  r9 ; 
 int /*<<< orphan*/  saved_context ; 
 int /*<<< orphan*/  saved_context_cr0 ; 
 int /*<<< orphan*/  saved_context_cr2 ; 
 int /*<<< orphan*/  saved_context_cr3 ; 
 int /*<<< orphan*/  saved_context_cr4 ; 
 int /*<<< orphan*/  saved_context_cr8 ; 
 int /*<<< orphan*/  saved_context_gdt_desc ; 
 int /*<<< orphan*/  si ; 
 int /*<<< orphan*/  sp ; 
 int /*<<< orphan*/  tss_struct ; 
 TYPE_1__ x86_tss ; 

int main(void)
{
#ifdef CONFIG_PARAVIRT
	OFFSET(PV_CPU_usergs_sysret64, pv_cpu_ops, usergs_sysret64);
	OFFSET(PV_CPU_swapgs, pv_cpu_ops, swapgs);
#ifdef CONFIG_DEBUG_ENTRY
	OFFSET(PV_IRQ_save_fl, pv_irq_ops, save_fl);
#endif
	BLANK();
#endif

#if defined(CONFIG_KVM_GUEST) && defined(CONFIG_PARAVIRT_SPINLOCKS)
	OFFSET(KVM_STEAL_TIME_preempted, kvm_steal_time, preempted);
	BLANK();
#endif

#define ENTRY(entry) OFFSET(pt_regs_ ## entry, pt_regs, entry)
	ENTRY(bx);
	ENTRY(cx);
	ENTRY(dx);
	ENTRY(sp);
	ENTRY(bp);
	ENTRY(si);
	ENTRY(di);
	ENTRY(r8);
	ENTRY(r9);
	ENTRY(r10);
	ENTRY(r11);
	ENTRY(r12);
	ENTRY(r13);
	ENTRY(r14);
	ENTRY(r15);
	ENTRY(flags);
	BLANK();
#undef ENTRY

#define ENTRY(entry) OFFSET(saved_context_ ## entry, saved_context, entry)
	ENTRY(cr0);
	ENTRY(cr2);
	ENTRY(cr3);
	ENTRY(cr4);
	ENTRY(cr8);
	ENTRY(gdt_desc);
	BLANK();
#undef ENTRY

	OFFSET(TSS_ist, tss_struct, x86_tss.ist);
	BLANK();

#ifdef CONFIG_STACKPROTECTOR
	DEFINE(stack_canary_offset, offsetof(union irq_stack_union, stack_canary));
	BLANK();
#endif

	DEFINE(__NR_syscall_max, sizeof(syscalls_64) - 1);
	DEFINE(NR_syscalls, sizeof(syscalls_64));

	DEFINE(__NR_syscall_compat_max, sizeof(syscalls_ia32) - 1);
	DEFINE(IA32_NR_syscalls, sizeof(syscalls_ia32));

	return 0;
}