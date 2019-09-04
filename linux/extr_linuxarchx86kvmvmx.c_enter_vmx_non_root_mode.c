#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vmcs12 {int vm_entry_controls; int cpu_based_vm_exec_control; scalar_t__ tsc_offset; int /*<<< orphan*/  vm_entry_msr_load_count; int /*<<< orphan*/  vm_entry_msr_load_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  vmcs02; void* vmcs01_guest_bndcfgs; void* vmcs01_debugctl; } ;
struct vcpu_vmx {int /*<<< orphan*/  vmcs01; TYPE_1__ nested; } ;
struct TYPE_4__ {int /*<<< orphan*/  tsc_offset; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int CPU_BASED_USE_TSC_OFFSETING ; 
 int CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int CPU_BASED_VIRTUAL_NMI_PENDING ; 
 int /*<<< orphan*/  CPU_BASED_VM_EXEC_CONTROL ; 
 int EXIT_REASON_INVALID_STATE ; 
 int EXIT_REASON_MSR_LOAD_FAIL ; 
 int /*<<< orphan*/  GUEST_BNDCFGS ; 
 int /*<<< orphan*/  GUEST_IA32_DEBUGCTL ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  KVM_REQ_GET_VMCS12_PAGES ; 
 int VM_ENTRY_LOAD_BNDCFGS ; 
 int VM_ENTRY_LOAD_DEBUG_CONTROLS ; 
 int /*<<< orphan*/  enter_guest_mode (struct kvm_vcpu*) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ kvm_mpx_supported () ; 
 scalar_t__ kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  leave_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  nested_get_vmcs12_pages (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_load_msr (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_vmcs02 (struct kvm_vcpu*,struct vmcs12*,int /*<<< orphan*/ *) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 void* vmcs_read64 (int /*<<< orphan*/ ) ; 
 int vmx_has_apicv_interrupt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_segment_cache_clear (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_switch_vmcs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enter_vmx_non_root_mode(struct kvm_vcpu *vcpu, u32 *exit_qual)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
	bool from_vmentry = !!exit_qual;
	u32 dummy_exit_qual;
	bool evaluate_pending_interrupts;
	int r = 0;

	evaluate_pending_interrupts = vmcs_read32(CPU_BASED_VM_EXEC_CONTROL) &
		(CPU_BASED_VIRTUAL_INTR_PENDING | CPU_BASED_VIRTUAL_NMI_PENDING);
	if (likely(!evaluate_pending_interrupts) && kvm_vcpu_apicv_active(vcpu))
		evaluate_pending_interrupts |= vmx_has_apicv_interrupt(vcpu);

	enter_guest_mode(vcpu);

	if (!(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS))
		vmx->nested.vmcs01_debugctl = vmcs_read64(GUEST_IA32_DEBUGCTL);
	if (kvm_mpx_supported() &&
		!(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS))
		vmx->nested.vmcs01_guest_bndcfgs = vmcs_read64(GUEST_BNDCFGS);

	vmx_switch_vmcs(vcpu, &vmx->nested.vmcs02);
	vmx_segment_cache_clear(vmx);

	if (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETING)
		vcpu->arch.tsc_offset += vmcs12->tsc_offset;

	r = EXIT_REASON_INVALID_STATE;
	if (prepare_vmcs02(vcpu, vmcs12, from_vmentry ? exit_qual : &dummy_exit_qual))
		goto fail;

	if (from_vmentry) {
		nested_get_vmcs12_pages(vcpu);

		r = EXIT_REASON_MSR_LOAD_FAIL;
		*exit_qual = nested_vmx_load_msr(vcpu,
	     					 vmcs12->vm_entry_msr_load_addr,
					      	 vmcs12->vm_entry_msr_load_count);
		if (*exit_qual)
			goto fail;
	} else {
		/*
		 * The MMU is not initialized to point at the right entities yet and
		 * "get pages" would need to read data from the guest (i.e. we will
		 * need to perform gpa to hpa translation). Request a call
		 * to nested_get_vmcs12_pages before the next VM-entry.  The MSRs
		 * have already been set at vmentry time and should not be reset.
		 */
		kvm_make_request(KVM_REQ_GET_VMCS12_PAGES, vcpu);
	}

	/*
	 * If L1 had a pending IRQ/NMI until it executed
	 * VMLAUNCH/VMRESUME which wasn't delivered because it was
	 * disallowed (e.g. interrupts disabled), L0 needs to
	 * evaluate if this pending event should cause an exit from L2
	 * to L1 or delivered directly to L2 (e.g. In case L1 don't
	 * intercept EXTERNAL_INTERRUPT).
	 *
	 * Usually this would be handled by the processor noticing an
	 * IRQ/NMI window request, or checking RVI during evaluation of
	 * pending virtual interrupts.  However, this setting was done
	 * on VMCS01 and now VMCS02 is active instead. Thus, we force L0
	 * to perform pending event evaluation by requesting a KVM_REQ_EVENT.
	 */
	if (unlikely(evaluate_pending_interrupts))
		kvm_make_request(KVM_REQ_EVENT, vcpu);

	/*
	 * Note no nested_vmx_succeed or nested_vmx_fail here. At this point
	 * we are no longer running L1, and VMLAUNCH/VMRESUME has not yet
	 * returned as far as L1 is concerned. It will only return (and set
	 * the success flag) when L2 exits (see nested_vmx_vmexit()).
	 */
	return 0;

fail:
	if (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETING)
		vcpu->arch.tsc_offset -= vmcs12->tsc_offset;
	leave_guest_mode(vcpu);
	vmx_switch_vmcs(vcpu, &vmx->vmcs01);
	return r;
}