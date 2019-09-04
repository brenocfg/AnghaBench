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
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ shadow_vmcs; } ;
struct vmcs12 {int launch_state; scalar_t__ guest_activity_state; int vm_entry_intr_info_field; int cpu_based_vm_exec_control; int guest_rflags; TYPE_1__ hdr; } ;
struct TYPE_8__ {int nested_run_pending; } ;
struct TYPE_6__ {int l1tf_flush_l1d; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;
struct vcpu_vmx {TYPE_4__ nested; TYPE_3__ vcpu; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int CPU_BASED_VIRTUAL_NMI_PENDING ; 
 int EXIT_REASON_INVALID_STATE ; 
 scalar_t__ GUEST_ACTIVITY_HLT ; 
 int INTR_INFO_VALID_MASK ; 
 int KVM_X86_SHADOW_INT_MOV_SS ; 
 int VMXERR_ENTRY_EVENTS_BLOCKED_BY_MOV_SS ; 
 int VMXERR_VMLAUNCH_NONCLEAR_VMCS ; 
 int VMXERR_VMRESUME_NONLAUNCHED_VMCS ; 
 int X86_EFLAGS_IF ; 
 int check_vmentry_postreqs (struct kvm_vcpu*,struct vmcs12*,int*) ; 
 int check_vmentry_prereqs (struct kvm_vcpu*,struct vmcs12*) ; 
 int /*<<< orphan*/  copy_shadow_to_vmcs12 (struct vcpu_vmx*) ; 
 scalar_t__ enable_shadow_vmcs ; 
 int enter_vmx_non_root_mode (struct kvm_vcpu*,int*) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int kvm_vcpu_halt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cache_shadow_vmcs12 (struct kvm_vcpu*,struct vmcs12*) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_check_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_entry_failure (struct kvm_vcpu*,struct vmcs12*,int,int) ; 
 int /*<<< orphan*/  nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_failValid (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  skip_emulated_instruction (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmx_get_interrupt_shadow (struct kvm_vcpu*) ; 

__attribute__((used)) static int nested_vmx_run(struct kvm_vcpu *vcpu, bool launch)
{
	struct vmcs12 *vmcs12;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u32 interrupt_shadow = vmx_get_interrupt_shadow(vcpu);
	u32 exit_qual;
	int ret;

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (!nested_vmx_check_vmcs12(vcpu))
		goto out;

	vmcs12 = get_vmcs12(vcpu);

	/*
	 * Can't VMLAUNCH or VMRESUME a shadow VMCS. Despite the fact
	 * that there *is* a valid VMCS pointer, RFLAGS.CF is set
	 * rather than RFLAGS.ZF, and no error number is stored to the
	 * VM-instruction error field.
	 */
	if (vmcs12->hdr.shadow_vmcs) {
		nested_vmx_failInvalid(vcpu);
		goto out;
	}

	if (enable_shadow_vmcs)
		copy_shadow_to_vmcs12(vmx);

	/*
	 * The nested entry process starts with enforcing various prerequisites
	 * on vmcs12 as required by the Intel SDM, and act appropriately when
	 * they fail: As the SDM explains, some conditions should cause the
	 * instruction to fail, while others will cause the instruction to seem
	 * to succeed, but return an EXIT_REASON_INVALID_STATE.
	 * To speed up the normal (success) code path, we should avoid checking
	 * for misconfigurations which will anyway be caught by the processor
	 * when using the merged vmcs02.
	 */
	if (interrupt_shadow & KVM_X86_SHADOW_INT_MOV_SS) {
		nested_vmx_failValid(vcpu,
				     VMXERR_ENTRY_EVENTS_BLOCKED_BY_MOV_SS);
		goto out;
	}

	if (vmcs12->launch_state == launch) {
		nested_vmx_failValid(vcpu,
			launch ? VMXERR_VMLAUNCH_NONCLEAR_VMCS
			       : VMXERR_VMRESUME_NONLAUNCHED_VMCS);
		goto out;
	}

	ret = check_vmentry_prereqs(vcpu, vmcs12);
	if (ret) {
		nested_vmx_failValid(vcpu, ret);
		goto out;
	}

	/*
	 * After this point, the trap flag no longer triggers a singlestep trap
	 * on the vm entry instructions; don't call kvm_skip_emulated_instruction.
	 * This is not 100% correct; for performance reasons, we delegate most
	 * of the checks on host state to the processor.  If those fail,
	 * the singlestep trap is missed.
	 */
	skip_emulated_instruction(vcpu);

	ret = check_vmentry_postreqs(vcpu, vmcs12, &exit_qual);
	if (ret) {
		nested_vmx_entry_failure(vcpu, vmcs12,
					 EXIT_REASON_INVALID_STATE, exit_qual);
		return 1;
	}

	/*
	 * We're finally done with prerequisite checking, and can start with
	 * the nested entry.
	 */

	vmx->nested.nested_run_pending = 1;
	ret = enter_vmx_non_root_mode(vcpu, &exit_qual);
	if (ret) {
		nested_vmx_entry_failure(vcpu, vmcs12, ret, exit_qual);
		vmx->nested.nested_run_pending = 0;
		return 1;
	}

	/* Hide L1D cache contents from the nested guest.  */
	vmx->vcpu.arch.l1tf_flush_l1d = true;

	/*
	 * Must happen outside of enter_vmx_non_root_mode() as it will
	 * also be used as part of restoring nVMX state for
	 * snapshot restore (migration).
	 *
	 * In this flow, it is assumed that vmcs12 cache was
	 * trasferred as part of captured nVMX state and should
	 * therefore not be read from guest memory (which may not
	 * exist on destination host yet).
	 */
	nested_cache_shadow_vmcs12(vcpu, vmcs12);

	/*
	 * If we're entering a halted L2 vcpu and the L2 vcpu won't be
	 * awakened by event injection or by an NMI-window VM-exit or
	 * by an interrupt-window VM-exit, halt the vcpu.
	 */
	if ((vmcs12->guest_activity_state == GUEST_ACTIVITY_HLT) &&
	    !(vmcs12->vm_entry_intr_info_field & INTR_INFO_VALID_MASK) &&
	    !(vmcs12->cpu_based_vm_exec_control & CPU_BASED_VIRTUAL_NMI_PENDING) &&
	    !((vmcs12->cpu_based_vm_exec_control & CPU_BASED_VIRTUAL_INTR_PENDING) &&
	      (vmcs12->guest_rflags & X86_EFLAGS_IF))) {
		vmx->nested.nested_run_pending = 0;
		return kvm_vcpu_halt(vcpu);
	}
	return 1;

out:
	return kvm_skip_emulated_instruction(vcpu);
}