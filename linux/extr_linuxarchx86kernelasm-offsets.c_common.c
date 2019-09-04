#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct entry_stack {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  code32_start; int /*<<< orphan*/  pref_address; int /*<<< orphan*/  init_size; int /*<<< orphan*/  kernel_alignment; int /*<<< orphan*/  version; int /*<<< orphan*/  hardware_subarch; int /*<<< orphan*/  loadflags; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr_limit; int /*<<< orphan*/  sp; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  sp1; int /*<<< orphan*/  sp0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  BP_code32_start ; 
 int /*<<< orphan*/  BP_hardware_subarch ; 
 int /*<<< orphan*/  BP_init_size ; 
 int /*<<< orphan*/  BP_kernel_alignment ; 
 int /*<<< orphan*/  BP_loadflags ; 
 int /*<<< orphan*/  BP_pref_address ; 
 int /*<<< orphan*/  BP_scratch ; 
 int /*<<< orphan*/  BP_secure_boot ; 
 int /*<<< orphan*/  BP_version ; 
 int /*<<< orphan*/  CPU_ENTRY_AREA_entry_stack ; 
 int /*<<< orphan*/  CPU_ENTRY_AREA_entry_trampoline ; 
 int /*<<< orphan*/  CPU_ENTRY_AREA_tss ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MASK_entry_stack ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTREGS_SIZE ; 
 int /*<<< orphan*/  SIZEOF_entry_stack ; 
 int /*<<< orphan*/  TASK_TI_flags ; 
 int /*<<< orphan*/  TASK_addr_limit ; 
 int /*<<< orphan*/  TASK_threadsp ; 
 int /*<<< orphan*/  TLB_STATE_user_pcid_flush_mask ; 
 int /*<<< orphan*/  TSS_sp0 ; 
 int /*<<< orphan*/  TSS_sp1 ; 
 int /*<<< orphan*/  __crt_ctx ; 
 int /*<<< orphan*/  address ; 
 int /*<<< orphan*/  boot_params ; 
 int /*<<< orphan*/  cpu_entry_area ; 
 int /*<<< orphan*/  crypto_tfm ; 
 int /*<<< orphan*/  crypto_tfm_ctx_offset ; 
 int /*<<< orphan*/  entry_stack_page ; 
 int /*<<< orphan*/  entry_trampoline ; 
 TYPE_4__ hdr ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  orig_address ; 
 int /*<<< orphan*/  pbe ; 
 int /*<<< orphan*/  pbe_address ; 
 int /*<<< orphan*/  pbe_next ; 
 int /*<<< orphan*/  pbe_orig_address ; 
 int /*<<< orphan*/  scratch ; 
 int /*<<< orphan*/  secure_boot ; 
 int /*<<< orphan*/  task_struct ; 
 TYPE_3__ thread ; 
 TYPE_2__ thread_info ; 
 int /*<<< orphan*/  tlb_state ; 
 int /*<<< orphan*/  tss ; 
 int /*<<< orphan*/  tss_struct ; 
 int /*<<< orphan*/  user_pcid_flush_mask ; 
 TYPE_1__ x86_tss ; 

void common(void) {
	BLANK();
	OFFSET(TASK_threadsp, task_struct, thread.sp);
#ifdef CONFIG_STACKPROTECTOR
	OFFSET(TASK_stack_canary, task_struct, stack_canary);
#endif

	BLANK();
	OFFSET(TASK_TI_flags, task_struct, thread_info.flags);
	OFFSET(TASK_addr_limit, task_struct, thread.addr_limit);

	BLANK();
	OFFSET(crypto_tfm_ctx_offset, crypto_tfm, __crt_ctx);

	BLANK();
	OFFSET(pbe_address, pbe, address);
	OFFSET(pbe_orig_address, pbe, orig_address);
	OFFSET(pbe_next, pbe, next);

#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
	BLANK();
	OFFSET(IA32_SIGCONTEXT_ax, sigcontext_32, ax);
	OFFSET(IA32_SIGCONTEXT_bx, sigcontext_32, bx);
	OFFSET(IA32_SIGCONTEXT_cx, sigcontext_32, cx);
	OFFSET(IA32_SIGCONTEXT_dx, sigcontext_32, dx);
	OFFSET(IA32_SIGCONTEXT_si, sigcontext_32, si);
	OFFSET(IA32_SIGCONTEXT_di, sigcontext_32, di);
	OFFSET(IA32_SIGCONTEXT_bp, sigcontext_32, bp);
	OFFSET(IA32_SIGCONTEXT_sp, sigcontext_32, sp);
	OFFSET(IA32_SIGCONTEXT_ip, sigcontext_32, ip);

	BLANK();
	OFFSET(IA32_RT_SIGFRAME_sigcontext, rt_sigframe_ia32, uc.uc_mcontext);
#endif

#ifdef CONFIG_PARAVIRT
	BLANK();
	OFFSET(PARAVIRT_PATCH_pv_cpu_ops, paravirt_patch_template, pv_cpu_ops);
	OFFSET(PARAVIRT_PATCH_pv_irq_ops, paravirt_patch_template, pv_irq_ops);
	OFFSET(PV_IRQ_irq_disable, pv_irq_ops, irq_disable);
	OFFSET(PV_IRQ_irq_enable, pv_irq_ops, irq_enable);
	OFFSET(PV_CPU_iret, pv_cpu_ops, iret);
	OFFSET(PV_CPU_read_cr0, pv_cpu_ops, read_cr0);
	OFFSET(PV_MMU_read_cr2, pv_mmu_ops, read_cr2);
#endif

#ifdef CONFIG_XEN
	BLANK();
	OFFSET(XEN_vcpu_info_mask, vcpu_info, evtchn_upcall_mask);
	OFFSET(XEN_vcpu_info_pending, vcpu_info, evtchn_upcall_pending);
#endif

	BLANK();
	OFFSET(BP_scratch, boot_params, scratch);
	OFFSET(BP_secure_boot, boot_params, secure_boot);
	OFFSET(BP_loadflags, boot_params, hdr.loadflags);
	OFFSET(BP_hardware_subarch, boot_params, hdr.hardware_subarch);
	OFFSET(BP_version, boot_params, hdr.version);
	OFFSET(BP_kernel_alignment, boot_params, hdr.kernel_alignment);
	OFFSET(BP_init_size, boot_params, hdr.init_size);
	OFFSET(BP_pref_address, boot_params, hdr.pref_address);
	OFFSET(BP_code32_start, boot_params, hdr.code32_start);

	BLANK();
	DEFINE(PTREGS_SIZE, sizeof(struct pt_regs));

	/* TLB state for the entry code */
	OFFSET(TLB_STATE_user_pcid_flush_mask, tlb_state, user_pcid_flush_mask);

	/* Layout info for cpu_entry_area */
	OFFSET(CPU_ENTRY_AREA_tss, cpu_entry_area, tss);
	OFFSET(CPU_ENTRY_AREA_entry_trampoline, cpu_entry_area, entry_trampoline);
	OFFSET(CPU_ENTRY_AREA_entry_stack, cpu_entry_area, entry_stack_page);
	DEFINE(SIZEOF_entry_stack, sizeof(struct entry_stack));
	DEFINE(MASK_entry_stack, (~(sizeof(struct entry_stack) - 1)));

	/* Offset for sp0 and sp1 into the tss_struct */
	OFFSET(TSS_sp0, tss_struct, x86_tss.sp0);
	OFFSET(TSS_sp1, tss_struct, x86_tss.sp1);
}