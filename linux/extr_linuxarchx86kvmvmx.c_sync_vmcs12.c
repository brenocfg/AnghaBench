#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vmcs12 {int vm_exit_controls; int vm_entry_controls; void* guest_bndcfgs; void* guest_sysenter_eip; void* guest_sysenter_esp; void* guest_sysenter_cs; int /*<<< orphan*/  guest_ia32_efer; void* guest_ia32_pat; void* guest_ia32_debugctl; int /*<<< orphan*/  guest_dr7; void* guest_intr_status; void* guest_linear_address; void* guest_pdptr3; void* guest_pdptr2; void* guest_pdptr1; void* guest_pdptr0; void* guest_cr3; int /*<<< orphan*/  vmx_preemption_timer_value; int /*<<< orphan*/  guest_activity_state; void* guest_pending_dbg_exceptions; void* guest_interruptibility_info; void* guest_idtr_base; void* guest_gdtr_base; void* guest_tr_base; void* guest_ldtr_base; void* guest_gs_base; void* guest_fs_base; void* guest_ds_base; void* guest_ss_base; void* guest_cs_base; void* guest_es_base; void* guest_tr_ar_bytes; void* guest_ldtr_ar_bytes; void* guest_gs_ar_bytes; void* guest_fs_ar_bytes; void* guest_ds_ar_bytes; void* guest_ss_ar_bytes; void* guest_cs_ar_bytes; void* guest_es_ar_bytes; void* guest_idtr_limit; void* guest_gdtr_limit; void* guest_tr_limit; void* guest_ldtr_limit; void* guest_gs_limit; void* guest_fs_limit; void* guest_ds_limit; void* guest_ss_limit; void* guest_cs_limit; void* guest_es_limit; void* guest_tr_selector; void* guest_ldtr_selector; void* guest_gs_selector; void* guest_fs_selector; void* guest_ds_selector; void* guest_ss_selector; void* guest_cs_selector; void* guest_es_selector; void* guest_rflags; void* guest_rip; void* guest_rsp; int /*<<< orphan*/  guest_cr4; int /*<<< orphan*/  guest_cr0; } ;
struct TYPE_6__ {scalar_t__ mp_state; int /*<<< orphan*/  efer; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  preemption_timer; } ;
struct TYPE_7__ {TYPE_1__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_ACTIVITY_ACTIVE ; 
 int /*<<< orphan*/  GUEST_ACTIVITY_HLT ; 
 int /*<<< orphan*/  GUEST_BNDCFGS ; 
 int /*<<< orphan*/  GUEST_CR3 ; 
 int /*<<< orphan*/  GUEST_CS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_CS_BASE ; 
 int /*<<< orphan*/  GUEST_CS_LIMIT ; 
 int /*<<< orphan*/  GUEST_CS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_DS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_DS_BASE ; 
 int /*<<< orphan*/  GUEST_DS_LIMIT ; 
 int /*<<< orphan*/  GUEST_DS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_ES_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_ES_BASE ; 
 int /*<<< orphan*/  GUEST_ES_LIMIT ; 
 int /*<<< orphan*/  GUEST_ES_SELECTOR ; 
 int /*<<< orphan*/  GUEST_FS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_FS_BASE ; 
 int /*<<< orphan*/  GUEST_FS_LIMIT ; 
 int /*<<< orphan*/  GUEST_FS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_GDTR_BASE ; 
 int /*<<< orphan*/  GUEST_GDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_GS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_GS_BASE ; 
 int /*<<< orphan*/  GUEST_GS_LIMIT ; 
 int /*<<< orphan*/  GUEST_GS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_IA32_DEBUGCTL ; 
 int /*<<< orphan*/  GUEST_IA32_PAT ; 
 int /*<<< orphan*/  GUEST_IDTR_BASE ; 
 int /*<<< orphan*/  GUEST_IDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int /*<<< orphan*/  GUEST_INTR_STATUS ; 
 int /*<<< orphan*/  GUEST_LDTR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_LDTR_BASE ; 
 int /*<<< orphan*/  GUEST_LDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_LDTR_SELECTOR ; 
 int /*<<< orphan*/  GUEST_LINEAR_ADDRESS ; 
 int /*<<< orphan*/  GUEST_PDPTR0 ; 
 int /*<<< orphan*/  GUEST_PDPTR1 ; 
 int /*<<< orphan*/  GUEST_PDPTR2 ; 
 int /*<<< orphan*/  GUEST_PDPTR3 ; 
 int /*<<< orphan*/  GUEST_PENDING_DBG_EXCEPTIONS ; 
 int /*<<< orphan*/  GUEST_RFLAGS ; 
 int /*<<< orphan*/  GUEST_SS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_SS_BASE ; 
 int /*<<< orphan*/  GUEST_SS_LIMIT ; 
 int /*<<< orphan*/  GUEST_SS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_SYSENTER_CS ; 
 int /*<<< orphan*/  GUEST_SYSENTER_EIP ; 
 int /*<<< orphan*/  GUEST_SYSENTER_ESP ; 
 int /*<<< orphan*/  GUEST_TR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_TR_BASE ; 
 int /*<<< orphan*/  GUEST_TR_LIMIT ; 
 int /*<<< orphan*/  GUEST_TR_SELECTOR ; 
 scalar_t__ KVM_MP_STATE_HALTED ; 
 int /*<<< orphan*/  VCPU_REGS_RIP ; 
 int /*<<< orphan*/  VCPU_REGS_RSP ; 
 int VM_ENTRY_IA32E_MODE ; 
 int VM_EXIT_SAVE_DEBUG_CONTROLS ; 
 int VM_EXIT_SAVE_IA32_EFER ; 
 int VM_EXIT_SAVE_IA32_PAT ; 
 int VM_EXIT_SAVE_VMX_PREEMPTION_TIMER ; 
 scalar_t__ enable_ept ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_get_dr (struct kvm_vcpu*,int,unsigned long*) ; 
 scalar_t__ kvm_mpx_supported () ; 
 void* kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has_preemption_timer (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_vid (struct vmcs12*) ; 
 TYPE_3__* to_vmx (struct kvm_vcpu*) ; 
 int vm_entry_controls_get (TYPE_3__*) ; 
 int /*<<< orphan*/  vmcs12_guest_cr0 (struct kvm_vcpu*,struct vmcs12*) ; 
 int /*<<< orphan*/  vmcs12_guest_cr4 (struct kvm_vcpu*,struct vmcs12*) ; 
 void* vmcs_read16 (int /*<<< orphan*/ ) ; 
 void* vmcs_read32 (int /*<<< orphan*/ ) ; 
 void* vmcs_read64 (int /*<<< orphan*/ ) ; 
 void* vmcs_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_get_preemption_timer_value (struct kvm_vcpu*) ; 

__attribute__((used)) static void sync_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
{
	vmcs12->guest_cr0 = vmcs12_guest_cr0(vcpu, vmcs12);
	vmcs12->guest_cr4 = vmcs12_guest_cr4(vcpu, vmcs12);

	vmcs12->guest_rsp = kvm_register_read(vcpu, VCPU_REGS_RSP);
	vmcs12->guest_rip = kvm_register_read(vcpu, VCPU_REGS_RIP);
	vmcs12->guest_rflags = vmcs_readl(GUEST_RFLAGS);

	vmcs12->guest_es_selector = vmcs_read16(GUEST_ES_SELECTOR);
	vmcs12->guest_cs_selector = vmcs_read16(GUEST_CS_SELECTOR);
	vmcs12->guest_ss_selector = vmcs_read16(GUEST_SS_SELECTOR);
	vmcs12->guest_ds_selector = vmcs_read16(GUEST_DS_SELECTOR);
	vmcs12->guest_fs_selector = vmcs_read16(GUEST_FS_SELECTOR);
	vmcs12->guest_gs_selector = vmcs_read16(GUEST_GS_SELECTOR);
	vmcs12->guest_ldtr_selector = vmcs_read16(GUEST_LDTR_SELECTOR);
	vmcs12->guest_tr_selector = vmcs_read16(GUEST_TR_SELECTOR);
	vmcs12->guest_es_limit = vmcs_read32(GUEST_ES_LIMIT);
	vmcs12->guest_cs_limit = vmcs_read32(GUEST_CS_LIMIT);
	vmcs12->guest_ss_limit = vmcs_read32(GUEST_SS_LIMIT);
	vmcs12->guest_ds_limit = vmcs_read32(GUEST_DS_LIMIT);
	vmcs12->guest_fs_limit = vmcs_read32(GUEST_FS_LIMIT);
	vmcs12->guest_gs_limit = vmcs_read32(GUEST_GS_LIMIT);
	vmcs12->guest_ldtr_limit = vmcs_read32(GUEST_LDTR_LIMIT);
	vmcs12->guest_tr_limit = vmcs_read32(GUEST_TR_LIMIT);
	vmcs12->guest_gdtr_limit = vmcs_read32(GUEST_GDTR_LIMIT);
	vmcs12->guest_idtr_limit = vmcs_read32(GUEST_IDTR_LIMIT);
	vmcs12->guest_es_ar_bytes = vmcs_read32(GUEST_ES_AR_BYTES);
	vmcs12->guest_cs_ar_bytes = vmcs_read32(GUEST_CS_AR_BYTES);
	vmcs12->guest_ss_ar_bytes = vmcs_read32(GUEST_SS_AR_BYTES);
	vmcs12->guest_ds_ar_bytes = vmcs_read32(GUEST_DS_AR_BYTES);
	vmcs12->guest_fs_ar_bytes = vmcs_read32(GUEST_FS_AR_BYTES);
	vmcs12->guest_gs_ar_bytes = vmcs_read32(GUEST_GS_AR_BYTES);
	vmcs12->guest_ldtr_ar_bytes = vmcs_read32(GUEST_LDTR_AR_BYTES);
	vmcs12->guest_tr_ar_bytes = vmcs_read32(GUEST_TR_AR_BYTES);
	vmcs12->guest_es_base = vmcs_readl(GUEST_ES_BASE);
	vmcs12->guest_cs_base = vmcs_readl(GUEST_CS_BASE);
	vmcs12->guest_ss_base = vmcs_readl(GUEST_SS_BASE);
	vmcs12->guest_ds_base = vmcs_readl(GUEST_DS_BASE);
	vmcs12->guest_fs_base = vmcs_readl(GUEST_FS_BASE);
	vmcs12->guest_gs_base = vmcs_readl(GUEST_GS_BASE);
	vmcs12->guest_ldtr_base = vmcs_readl(GUEST_LDTR_BASE);
	vmcs12->guest_tr_base = vmcs_readl(GUEST_TR_BASE);
	vmcs12->guest_gdtr_base = vmcs_readl(GUEST_GDTR_BASE);
	vmcs12->guest_idtr_base = vmcs_readl(GUEST_IDTR_BASE);

	vmcs12->guest_interruptibility_info =
		vmcs_read32(GUEST_INTERRUPTIBILITY_INFO);
	vmcs12->guest_pending_dbg_exceptions =
		vmcs_readl(GUEST_PENDING_DBG_EXCEPTIONS);
	if (vcpu->arch.mp_state == KVM_MP_STATE_HALTED)
		vmcs12->guest_activity_state = GUEST_ACTIVITY_HLT;
	else
		vmcs12->guest_activity_state = GUEST_ACTIVITY_ACTIVE;

	if (nested_cpu_has_preemption_timer(vmcs12)) {
		if (vmcs12->vm_exit_controls &
		    VM_EXIT_SAVE_VMX_PREEMPTION_TIMER)
			vmcs12->vmx_preemption_timer_value =
				vmx_get_preemption_timer_value(vcpu);
		hrtimer_cancel(&to_vmx(vcpu)->nested.preemption_timer);
	}

	/*
	 * In some cases (usually, nested EPT), L2 is allowed to change its
	 * own CR3 without exiting. If it has changed it, we must keep it.
	 * Of course, if L0 is using shadow page tables, GUEST_CR3 was defined
	 * by L0, not L1 or L2, so we mustn't unconditionally copy it to vmcs12.
	 *
	 * Additionally, restore L2's PDPTR to vmcs12.
	 */
	if (enable_ept) {
		vmcs12->guest_cr3 = vmcs_readl(GUEST_CR3);
		vmcs12->guest_pdptr0 = vmcs_read64(GUEST_PDPTR0);
		vmcs12->guest_pdptr1 = vmcs_read64(GUEST_PDPTR1);
		vmcs12->guest_pdptr2 = vmcs_read64(GUEST_PDPTR2);
		vmcs12->guest_pdptr3 = vmcs_read64(GUEST_PDPTR3);
	}

	vmcs12->guest_linear_address = vmcs_readl(GUEST_LINEAR_ADDRESS);

	if (nested_cpu_has_vid(vmcs12))
		vmcs12->guest_intr_status = vmcs_read16(GUEST_INTR_STATUS);

	vmcs12->vm_entry_controls =
		(vmcs12->vm_entry_controls & ~VM_ENTRY_IA32E_MODE) |
		(vm_entry_controls_get(to_vmx(vcpu)) & VM_ENTRY_IA32E_MODE);

	if (vmcs12->vm_exit_controls & VM_EXIT_SAVE_DEBUG_CONTROLS) {
		kvm_get_dr(vcpu, 7, (unsigned long *)&vmcs12->guest_dr7);
		vmcs12->guest_ia32_debugctl = vmcs_read64(GUEST_IA32_DEBUGCTL);
	}

	/* TODO: These cannot have changed unless we have MSR bitmaps and
	 * the relevant bit asks not to trap the change */
	if (vmcs12->vm_exit_controls & VM_EXIT_SAVE_IA32_PAT)
		vmcs12->guest_ia32_pat = vmcs_read64(GUEST_IA32_PAT);
	if (vmcs12->vm_exit_controls & VM_EXIT_SAVE_IA32_EFER)
		vmcs12->guest_ia32_efer = vcpu->arch.efer;
	vmcs12->guest_sysenter_cs = vmcs_read32(GUEST_SYSENTER_CS);
	vmcs12->guest_sysenter_esp = vmcs_readl(GUEST_SYSENTER_ESP);
	vmcs12->guest_sysenter_eip = vmcs_readl(GUEST_SYSENTER_EIP);
	if (kvm_mpx_supported())
		vmcs12->guest_bndcfgs = vmcs_read64(GUEST_BNDCFGS);
}