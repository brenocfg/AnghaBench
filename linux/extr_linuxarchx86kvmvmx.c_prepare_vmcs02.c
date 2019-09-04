#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vmcs12 {int guest_cs_limit; int guest_cs_ar_bytes; int vm_entry_controls; unsigned long long guest_ia32_debugctl; int vm_entry_intr_info_field; int vm_entry_exception_error_code; int vm_entry_instruction_len; int guest_interruptibility_info; int pin_based_vm_exec_control; int secondary_vm_exec_control; int cpu_based_vm_exec_control; int tpr_threshold; unsigned long long guest_ia32_pat; scalar_t__ virtual_processor_id; int guest_ia32_efer; int /*<<< orphan*/  guest_rip; int /*<<< orphan*/  guest_rsp; int /*<<< orphan*/  guest_cr3; int /*<<< orphan*/  guest_cr4; int /*<<< orphan*/  guest_cr0; int /*<<< orphan*/  cr0_guest_host_mask; scalar_t__ guest_intr_status; int /*<<< orphan*/  posted_intr_nv; int /*<<< orphan*/  guest_rflags; int /*<<< orphan*/  guest_dr7; int /*<<< orphan*/  guest_cs_base; int /*<<< orphan*/  guest_es_base; scalar_t__ guest_cs_selector; } ;
struct TYPE_13__ {int dirty_vmcs12; unsigned long long vmcs01_debugctl; int pi_pending; int preemption_timer_expired; scalar_t__ last_vpid; scalar_t__ nested_run_pending; scalar_t__ vpid02; int /*<<< orphan*/  posted_intr_nv; } ;
struct TYPE_8__ {unsigned long long pat; } ;
struct TYPE_9__ {TYPE_1__ arch; } ;
struct vcpu_vmx {int secondary_exec_control; scalar_t__ emulation_required; TYPE_6__ nested; int /*<<< orphan*/  pml_pg; TYPE_2__ vcpu; scalar_t__ host_rsp; TYPE_4__* loaded_vmcs; } ;
struct TYPE_12__ {unsigned long long pat; unsigned long long tsc_offset; int efer; TYPE_3__* walk_mmu; int /*<<< orphan*/  cr0_guest_owned_bits; int /*<<< orphan*/  dr7; } ;
struct kvm_vcpu {TYPE_5__ arch; } ;
struct TYPE_14__ {int pin_based_exec_ctrl; int vmexit_ctrl; int vmentry_ctrl; } ;
struct TYPE_11__ {int nmi_known_unmasked; int hv_timer_armed; } ;
struct TYPE_10__ {int /*<<< orphan*/  inject_page_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ACCESS_ADDR ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_BASED_ACTIVATE_SECONDARY_CONTROLS ; 
 int CPU_BASED_TPR_SHADOW ; 
 int CPU_BASED_UNCOND_IO_EXITING ; 
 int CPU_BASED_USE_IO_BITMAPS ; 
 int CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int CPU_BASED_VIRTUAL_NMI_PENDING ; 
 int /*<<< orphan*/  CPU_BASED_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  CR0_GUEST_HOST_MASK ; 
 int /*<<< orphan*/  CR0_READ_SHADOW ; 
 int /*<<< orphan*/  CR4_READ_SHADOW ; 
 int EFER_LMA ; 
 int EFER_LME ; 
 int /*<<< orphan*/  ENCLS_EXITING_BITMAP ; 
 int ENTRY_FAIL_DEFAULT ; 
 int /*<<< orphan*/  GUEST_CS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_CS_BASE ; 
 int /*<<< orphan*/  GUEST_CS_LIMIT ; 
 int /*<<< orphan*/  GUEST_CS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_ES_BASE ; 
 int /*<<< orphan*/  GUEST_IA32_DEBUGCTL ; 
 int /*<<< orphan*/  GUEST_IA32_PAT ; 
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int GUEST_INTR_STATE_NMI ; 
 int /*<<< orphan*/  GUEST_INTR_STATUS ; 
 int /*<<< orphan*/  GUEST_PML_INDEX ; 
 int PIN_BASED_POSTED_INTR ; 
 int PIN_BASED_VMX_PREEMPTION_TIMER ; 
 int /*<<< orphan*/  PIN_BASED_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  PML_ADDRESS ; 
 scalar_t__ PML_ENTITY_NUM ; 
 int SECONDARY_EXEC_APIC_REGISTER_VIRT ; 
 int SECONDARY_EXEC_ENABLE_INVPCID ; 
 int SECONDARY_EXEC_ENABLE_PML ; 
 int SECONDARY_EXEC_ENABLE_VMFUNC ; 
 int SECONDARY_EXEC_ENCLS_EXITING ; 
 int SECONDARY_EXEC_RDTSCP ; 
 int SECONDARY_EXEC_SHADOW_VMCS ; 
 int SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES ; 
 int SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY ; 
 int SECONDARY_EXEC_XSAVES ; 
 int /*<<< orphan*/  SECONDARY_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  TPR_THRESHOLD ; 
 int /*<<< orphan*/  TSC_OFFSET ; 
 int /*<<< orphan*/  VCPU_REGS_RIP ; 
 int /*<<< orphan*/  VCPU_REGS_RSP ; 
 int /*<<< orphan*/  VIRTUAL_APIC_PAGE_ADDR ; 
 int /*<<< orphan*/  VM_ENTRY_EXCEPTION_ERROR_CODE ; 
 int VM_ENTRY_IA32E_MODE ; 
 int /*<<< orphan*/  VM_ENTRY_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  VM_ENTRY_INTR_INFO_FIELD ; 
 int VM_ENTRY_LOAD_DEBUG_CONTROLS ; 
 int VM_ENTRY_LOAD_IA32_EFER ; 
 int VM_ENTRY_LOAD_IA32_PAT ; 
 int /*<<< orphan*/  VM_EXIT_CONTROLS ; 
 int /*<<< orphan*/  __vmx_flush_tlb (struct kvm_vcpu*,scalar_t__,int) ; 
 scalar_t__ cpu_has_secondary_exec_ctrls () ; 
 int /*<<< orphan*/  decache_tsc_multiplier (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  enable_ept ; 
 scalar_t__ enable_pml ; 
 scalar_t__ enable_vpid ; 
 scalar_t__ kvm_has_tsc_control ; 
 int /*<<< orphan*/  kvm_register_write (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_dr (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has2 (struct vmcs12*,int) ; 
 scalar_t__ nested_cpu_has_ept (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_posted_intr (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_preemption_timer (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_vpid (struct vmcs12*) ; 
 scalar_t__ nested_ept_init_mmu_context (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_read_cr0 (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_read_cr4 (struct vmcs12*) ; 
 scalar_t__ nested_vmx_load_cr3 (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 unsigned long long page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_vmcs02_full (struct kvm_vcpu*,struct vmcs12*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_exception_bitmap (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vm_entry_controls_init (struct vcpu_vmx*,int) ; 
 TYPE_7__ vmcs_config ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmx_exec_control (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_flush_tlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vmx_inject_page_fault_nested ; 
 int /*<<< orphan*/  vmx_set_cr0 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_cr4 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_efer (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vmx_set_rflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_start_preemption_timer (struct kvm_vcpu*) ; 

__attribute__((used)) static int prepare_vmcs02(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12,
			  u32 *entry_failure_code)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u32 exec_control, vmcs12_exec_ctrl;

	if (vmx->nested.dirty_vmcs12) {
		prepare_vmcs02_full(vcpu, vmcs12);
		vmx->nested.dirty_vmcs12 = false;
	}

	/*
	 * First, the fields that are shadowed.  This must be kept in sync
	 * with vmx_shadow_fields.h.
	 */

	vmcs_write16(GUEST_CS_SELECTOR, vmcs12->guest_cs_selector);
	vmcs_write32(GUEST_CS_LIMIT, vmcs12->guest_cs_limit);
	vmcs_write32(GUEST_CS_AR_BYTES, vmcs12->guest_cs_ar_bytes);
	vmcs_writel(GUEST_ES_BASE, vmcs12->guest_es_base);
	vmcs_writel(GUEST_CS_BASE, vmcs12->guest_cs_base);

	if (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS)) {
		kvm_set_dr(vcpu, 7, vmcs12->guest_dr7);
		vmcs_write64(GUEST_IA32_DEBUGCTL, vmcs12->guest_ia32_debugctl);
	} else {
		kvm_set_dr(vcpu, 7, vcpu->arch.dr7);
		vmcs_write64(GUEST_IA32_DEBUGCTL, vmx->nested.vmcs01_debugctl);
	}
	if (vmx->nested.nested_run_pending) {
		vmcs_write32(VM_ENTRY_INTR_INFO_FIELD,
			     vmcs12->vm_entry_intr_info_field);
		vmcs_write32(VM_ENTRY_EXCEPTION_ERROR_CODE,
			     vmcs12->vm_entry_exception_error_code);
		vmcs_write32(VM_ENTRY_INSTRUCTION_LEN,
			     vmcs12->vm_entry_instruction_len);
		vmcs_write32(GUEST_INTERRUPTIBILITY_INFO,
			     vmcs12->guest_interruptibility_info);
		vmx->loaded_vmcs->nmi_known_unmasked =
			!(vmcs12->guest_interruptibility_info & GUEST_INTR_STATE_NMI);
	} else {
		vmcs_write32(VM_ENTRY_INTR_INFO_FIELD, 0);
	}
	vmx_set_rflags(vcpu, vmcs12->guest_rflags);

	exec_control = vmcs12->pin_based_vm_exec_control;

	/* Preemption timer setting is computed directly in vmx_vcpu_run.  */
	exec_control |= vmcs_config.pin_based_exec_ctrl;
	exec_control &= ~PIN_BASED_VMX_PREEMPTION_TIMER;
	vmx->loaded_vmcs->hv_timer_armed = false;

	/* Posted interrupts setting is only taken from vmcs12.  */
	if (nested_cpu_has_posted_intr(vmcs12)) {
		vmx->nested.posted_intr_nv = vmcs12->posted_intr_nv;
		vmx->nested.pi_pending = false;
	} else {
		exec_control &= ~PIN_BASED_POSTED_INTR;
	}

	vmcs_write32(PIN_BASED_VM_EXEC_CONTROL, exec_control);

	vmx->nested.preemption_timer_expired = false;
	if (nested_cpu_has_preemption_timer(vmcs12))
		vmx_start_preemption_timer(vcpu);

	if (cpu_has_secondary_exec_ctrls()) {
		exec_control = vmx->secondary_exec_control;

		/* Take the following fields only from vmcs12 */
		exec_control &= ~(SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |
				  SECONDARY_EXEC_ENABLE_INVPCID |
				  SECONDARY_EXEC_RDTSCP |
				  SECONDARY_EXEC_XSAVES |
				  SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY |
				  SECONDARY_EXEC_APIC_REGISTER_VIRT |
				  SECONDARY_EXEC_ENABLE_VMFUNC);
		if (nested_cpu_has(vmcs12,
				   CPU_BASED_ACTIVATE_SECONDARY_CONTROLS)) {
			vmcs12_exec_ctrl = vmcs12->secondary_vm_exec_control &
				~SECONDARY_EXEC_ENABLE_PML;
			exec_control |= vmcs12_exec_ctrl;
		}

		/* VMCS shadowing for L2 is emulated for now */
		exec_control &= ~SECONDARY_EXEC_SHADOW_VMCS;

		if (exec_control & SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY)
			vmcs_write16(GUEST_INTR_STATUS,
				vmcs12->guest_intr_status);

		/*
		 * Write an illegal value to APIC_ACCESS_ADDR. Later,
		 * nested_get_vmcs12_pages will either fix it up or
		 * remove the VM execution control.
		 */
		if (exec_control & SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES)
			vmcs_write64(APIC_ACCESS_ADDR, -1ull);

		if (exec_control & SECONDARY_EXEC_ENCLS_EXITING)
			vmcs_write64(ENCLS_EXITING_BITMAP, -1ull);

		vmcs_write32(SECONDARY_VM_EXEC_CONTROL, exec_control);
	}

	/*
	 * HOST_RSP is normally set correctly in vmx_vcpu_run() just before
	 * entry, but only if the current (host) sp changed from the value
	 * we wrote last (vmx->host_rsp). This cache is no longer relevant
	 * if we switch vmcs, and rather than hold a separate cache per vmcs,
	 * here we just force the write to happen on entry.
	 */
	vmx->host_rsp = 0;

	exec_control = vmx_exec_control(vmx); /* L0's desires */
	exec_control &= ~CPU_BASED_VIRTUAL_INTR_PENDING;
	exec_control &= ~CPU_BASED_VIRTUAL_NMI_PENDING;
	exec_control &= ~CPU_BASED_TPR_SHADOW;
	exec_control |= vmcs12->cpu_based_vm_exec_control;

	/*
	 * Write an illegal value to VIRTUAL_APIC_PAGE_ADDR. Later, if
	 * nested_get_vmcs12_pages can't fix it up, the illegal value
	 * will result in a VM entry failure.
	 */
	if (exec_control & CPU_BASED_TPR_SHADOW) {
		vmcs_write64(VIRTUAL_APIC_PAGE_ADDR, -1ull);
		vmcs_write32(TPR_THRESHOLD, vmcs12->tpr_threshold);
	} else {
#ifdef CONFIG_X86_64
		exec_control |= CPU_BASED_CR8_LOAD_EXITING |
				CPU_BASED_CR8_STORE_EXITING;
#endif
	}

	/*
	 * A vmexit (to either L1 hypervisor or L0 userspace) is always needed
	 * for I/O port accesses.
	 */
	exec_control &= ~CPU_BASED_USE_IO_BITMAPS;
	exec_control |= CPU_BASED_UNCOND_IO_EXITING;

	vmcs_write32(CPU_BASED_VM_EXEC_CONTROL, exec_control);

	/* EXCEPTION_BITMAP and CR0_GUEST_HOST_MASK should basically be the
	 * bitwise-or of what L1 wants to trap for L2, and what we want to
	 * trap. Note that CR0.TS also needs updating - we do this later.
	 */
	update_exception_bitmap(vcpu);
	vcpu->arch.cr0_guest_owned_bits &= ~vmcs12->cr0_guest_host_mask;
	vmcs_writel(CR0_GUEST_HOST_MASK, ~vcpu->arch.cr0_guest_owned_bits);

	/* L2->L1 exit controls are emulated - the hardware exit is to L0 so
	 * we should use its exit controls. Note that VM_EXIT_LOAD_IA32_EFER
	 * bits are further modified by vmx_set_efer() below.
	 */
	vmcs_write32(VM_EXIT_CONTROLS, vmcs_config.vmexit_ctrl);

	/* vmcs12's VM_ENTRY_LOAD_IA32_EFER and VM_ENTRY_IA32E_MODE are
	 * emulated by vmx_set_efer(), below.
	 */
	vm_entry_controls_init(vmx, 
		(vmcs12->vm_entry_controls & ~VM_ENTRY_LOAD_IA32_EFER &
			~VM_ENTRY_IA32E_MODE) |
		(vmcs_config.vmentry_ctrl & ~VM_ENTRY_IA32E_MODE));

	if (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_PAT)) {
		vmcs_write64(GUEST_IA32_PAT, vmcs12->guest_ia32_pat);
		vcpu->arch.pat = vmcs12->guest_ia32_pat;
	} else if (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT) {
		vmcs_write64(GUEST_IA32_PAT, vmx->vcpu.arch.pat);
	}

	vmcs_write64(TSC_OFFSET, vcpu->arch.tsc_offset);

	if (kvm_has_tsc_control)
		decache_tsc_multiplier(vmx);

	if (enable_vpid) {
		/*
		 * There is no direct mapping between vpid02 and vpid12, the
		 * vpid02 is per-vCPU for L0 and reused while the value of
		 * vpid12 is changed w/ one invvpid during nested vmentry.
		 * The vpid12 is allocated by L1 for L2, so it will not
		 * influence global bitmap(for vpid01 and vpid02 allocation)
		 * even if spawn a lot of nested vCPUs.
		 */
		if (nested_cpu_has_vpid(vmcs12) && vmx->nested.vpid02) {
			if (vmcs12->virtual_processor_id != vmx->nested.last_vpid) {
				vmx->nested.last_vpid = vmcs12->virtual_processor_id;
				__vmx_flush_tlb(vcpu, vmx->nested.vpid02, true);
			}
		} else {
			vmx_flush_tlb(vcpu, true);
		}
	}

	if (enable_pml) {
		/*
		 * Conceptually we want to copy the PML address and index from
		 * vmcs01 here, and then back to vmcs01 on nested vmexit. But,
		 * since we always flush the log on each vmexit, this happens
		 * to be equivalent to simply resetting the fields in vmcs02.
		 */
		ASSERT(vmx->pml_pg);
		vmcs_write64(PML_ADDRESS, page_to_phys(vmx->pml_pg));
		vmcs_write16(GUEST_PML_INDEX, PML_ENTITY_NUM - 1);
	}

	if (nested_cpu_has_ept(vmcs12)) {
		if (nested_ept_init_mmu_context(vcpu)) {
			*entry_failure_code = ENTRY_FAIL_DEFAULT;
			return 1;
		}
	} else if (nested_cpu_has2(vmcs12,
				   SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES)) {
		vmx_flush_tlb(vcpu, true);
	}

	/*
	 * This sets GUEST_CR0 to vmcs12->guest_cr0, possibly modifying those
	 * bits which we consider mandatory enabled.
	 * The CR0_READ_SHADOW is what L2 should have expected to read given
	 * the specifications by L1; It's not enough to take
	 * vmcs12->cr0_read_shadow because on our cr0_guest_host_mask we we
	 * have more bits than L1 expected.
	 */
	vmx_set_cr0(vcpu, vmcs12->guest_cr0);
	vmcs_writel(CR0_READ_SHADOW, nested_read_cr0(vmcs12));

	vmx_set_cr4(vcpu, vmcs12->guest_cr4);
	vmcs_writel(CR4_READ_SHADOW, nested_read_cr4(vmcs12));

	if (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_EFER))
		vcpu->arch.efer = vmcs12->guest_ia32_efer;
	else if (vmcs12->vm_entry_controls & VM_ENTRY_IA32E_MODE)
		vcpu->arch.efer |= (EFER_LMA | EFER_LME);
	else
		vcpu->arch.efer &= ~(EFER_LMA | EFER_LME);
	/* Note: modifies VM_ENTRY/EXIT_CONTROLS and GUEST/HOST_IA32_EFER */
	vmx_set_efer(vcpu, vcpu->arch.efer);

	/*
	 * Guest state is invalid and unrestricted guest is disabled,
	 * which means L1 attempted VMEntry to L2 with invalid state.
	 * Fail the VMEntry.
	 */
	if (vmx->emulation_required) {
		*entry_failure_code = ENTRY_FAIL_DEFAULT;
		return 1;
	}

	/* Shadow page tables on either EPT or shadow page tables. */
	if (nested_vmx_load_cr3(vcpu, vmcs12->guest_cr3, nested_cpu_has_ept(vmcs12),
				entry_failure_code))
		return 1;

	if (!enable_ept)
		vcpu->arch.walk_mmu->inject_page_fault = vmx_inject_page_fault_nested;

	kvm_register_write(vcpu, VCPU_REGS_RSP, vmcs12->guest_rsp);
	kvm_register_write(vcpu, VCPU_REGS_RIP, vmcs12->guest_rip);
	return 0;
}