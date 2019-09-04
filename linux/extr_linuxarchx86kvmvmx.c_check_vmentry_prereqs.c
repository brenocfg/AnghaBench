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
typedef  int u8 ;
typedef  int u32 ;
struct vmcs12 {scalar_t__ guest_activity_state; int vm_function_control; scalar_t__ cr3_target_count; int vm_entry_intr_info_field; int guest_cr0; int vm_entry_exception_error_code; int vm_entry_instruction_len; int /*<<< orphan*/  host_cr3; int /*<<< orphan*/  host_cr4; int /*<<< orphan*/  host_cr0; int /*<<< orphan*/  eptp_list_address; int /*<<< orphan*/  vm_entry_controls; int /*<<< orphan*/  vm_exit_controls; int /*<<< orphan*/  pin_based_vm_exec_control; int /*<<< orphan*/  secondary_vm_exec_control; int /*<<< orphan*/  cpu_based_vm_exec_control; int /*<<< orphan*/  virtual_processor_id; } ;
struct TYPE_3__ {int vmfunc_controls; int /*<<< orphan*/  entry_ctls_high; int /*<<< orphan*/  entry_ctls_low; int /*<<< orphan*/  exit_ctls_high; int /*<<< orphan*/  exit_ctls_low; int /*<<< orphan*/  pinbased_ctls_high; int /*<<< orphan*/  pinbased_ctls_low; int /*<<< orphan*/  secondary_ctls_high; int /*<<< orphan*/  secondary_ctls_low; int /*<<< orphan*/  procbased_ctls_high; int /*<<< orphan*/  procbased_ctls_low; } ;
struct TYPE_4__ {TYPE_1__ msrs; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_ACTIVATE_SECONDARY_CONTROLS ; 
 int GENMASK (int,int) ; 
 scalar_t__ GUEST_ACTIVITY_ACTIVE ; 
 scalar_t__ GUEST_ACTIVITY_HLT ; 
 int INTR_INFO_DELIVER_CODE_MASK ; 
 int INTR_INFO_INTR_TYPE_MASK ; 
 int INTR_INFO_RESVD_BITS_MASK ; 
 int INTR_INFO_VALID_MASK ; 
 int INTR_INFO_VECTOR_MASK ; 
 int INTR_TYPE_HARD_EXCEPTION ; 
 int INTR_TYPE_NMI_INTR ; 
 int INTR_TYPE_OTHER_EVENT ; 
#define  INTR_TYPE_PRIV_SW_EXCEPTION 130 
 int INTR_TYPE_RESERVED ; 
#define  INTR_TYPE_SOFT_EXCEPTION 129 
#define  INTR_TYPE_SOFT_INTR 128 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  SECONDARY_EXEC_UNRESTRICTED_GUEST ; 
 int VMXERR_ENTRY_INVALID_CONTROL_FIELD ; 
 int VMXERR_ENTRY_INVALID_HOST_STATE_FIELD ; 
 int X86_CR0_PE ; 
 scalar_t__ nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int nested_cpu_has2 (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_ept (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_eptp_switching (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_vmfunc (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_vpid (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_cpu_has_zero_length_injection (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cpu_supports_monitor_trap_flag (struct kvm_vcpu*) ; 
 scalar_t__ nested_cpu_vmx_misc_cr3_count (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cr3_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_host_cr0_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_host_cr4_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_vmx_check_apic_access_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_apicv_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_io_bitmap_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_msr_bitmap_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_msr_switch_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_nmi_controls (struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_pml_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_shadow_vmcs_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_tpr_shadow_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 int /*<<< orphan*/  page_address_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_control_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ x86_exception_has_error_code (int) ; 

__attribute__((used)) static int check_vmentry_prereqs(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (vmcs12->guest_activity_state != GUEST_ACTIVITY_ACTIVE &&
	    vmcs12->guest_activity_state != GUEST_ACTIVITY_HLT)
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_cpu_has_vpid(vmcs12) && !vmcs12->virtual_processor_id)
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_io_bitmap_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_msr_bitmap_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_apic_access_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_tpr_shadow_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_apicv_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_msr_switch_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_pml_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_shadow_vmcs_controls(vcpu, vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (!vmx_control_verify(vmcs12->cpu_based_vm_exec_control,
				vmx->nested.msrs.procbased_ctls_low,
				vmx->nested.msrs.procbased_ctls_high) ||
	    (nested_cpu_has(vmcs12, CPU_BASED_ACTIVATE_SECONDARY_CONTROLS) &&
	     !vmx_control_verify(vmcs12->secondary_vm_exec_control,
				 vmx->nested.msrs.secondary_ctls_low,
				 vmx->nested.msrs.secondary_ctls_high)) ||
	    !vmx_control_verify(vmcs12->pin_based_vm_exec_control,
				vmx->nested.msrs.pinbased_ctls_low,
				vmx->nested.msrs.pinbased_ctls_high) ||
	    !vmx_control_verify(vmcs12->vm_exit_controls,
				vmx->nested.msrs.exit_ctls_low,
				vmx->nested.msrs.exit_ctls_high) ||
	    !vmx_control_verify(vmcs12->vm_entry_controls,
				vmx->nested.msrs.entry_ctls_low,
				vmx->nested.msrs.entry_ctls_high))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_vmx_check_nmi_controls(vmcs12))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (nested_cpu_has_vmfunc(vmcs12)) {
		if (vmcs12->vm_function_control &
		    ~vmx->nested.msrs.vmfunc_controls)
			return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

		if (nested_cpu_has_eptp_switching(vmcs12)) {
			if (!nested_cpu_has_ept(vmcs12) ||
			    !page_address_valid(vcpu, vmcs12->eptp_list_address))
				return VMXERR_ENTRY_INVALID_CONTROL_FIELD;
		}
	}

	if (vmcs12->cr3_target_count > nested_cpu_vmx_misc_cr3_count(vcpu))
		return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

	if (!nested_host_cr0_valid(vcpu, vmcs12->host_cr0) ||
	    !nested_host_cr4_valid(vcpu, vmcs12->host_cr4) ||
	    !nested_cr3_valid(vcpu, vmcs12->host_cr3))
		return VMXERR_ENTRY_INVALID_HOST_STATE_FIELD;

	/*
	 * From the Intel SDM, volume 3:
	 * Fields relevant to VM-entry event injection must be set properly.
	 * These fields are the VM-entry interruption-information field, the
	 * VM-entry exception error code, and the VM-entry instruction length.
	 */
	if (vmcs12->vm_entry_intr_info_field & INTR_INFO_VALID_MASK) {
		u32 intr_info = vmcs12->vm_entry_intr_info_field;
		u8 vector = intr_info & INTR_INFO_VECTOR_MASK;
		u32 intr_type = intr_info & INTR_INFO_INTR_TYPE_MASK;
		bool has_error_code = intr_info & INTR_INFO_DELIVER_CODE_MASK;
		bool should_have_error_code;
		bool urg = nested_cpu_has2(vmcs12,
					   SECONDARY_EXEC_UNRESTRICTED_GUEST);
		bool prot_mode = !urg || vmcs12->guest_cr0 & X86_CR0_PE;

		/* VM-entry interruption-info field: interruption type */
		if (intr_type == INTR_TYPE_RESERVED ||
		    (intr_type == INTR_TYPE_OTHER_EVENT &&
		     !nested_cpu_supports_monitor_trap_flag(vcpu)))
			return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

		/* VM-entry interruption-info field: vector */
		if ((intr_type == INTR_TYPE_NMI_INTR && vector != NMI_VECTOR) ||
		    (intr_type == INTR_TYPE_HARD_EXCEPTION && vector > 31) ||
		    (intr_type == INTR_TYPE_OTHER_EVENT && vector != 0))
			return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

		/* VM-entry interruption-info field: deliver error code */
		should_have_error_code =
			intr_type == INTR_TYPE_HARD_EXCEPTION && prot_mode &&
			x86_exception_has_error_code(vector);
		if (has_error_code != should_have_error_code)
			return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

		/* VM-entry exception error code */
		if (has_error_code &&
		    vmcs12->vm_entry_exception_error_code & GENMASK(31, 15))
			return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

		/* VM-entry interruption-info field: reserved bits */
		if (intr_info & INTR_INFO_RESVD_BITS_MASK)
			return VMXERR_ENTRY_INVALID_CONTROL_FIELD;

		/* VM-entry instruction length */
		switch (intr_type) {
		case INTR_TYPE_SOFT_EXCEPTION:
		case INTR_TYPE_SOFT_INTR:
		case INTR_TYPE_PRIV_SW_EXCEPTION:
			if ((vmcs12->vm_entry_instruction_len > 15) ||
			    (vmcs12->vm_entry_instruction_len == 0 &&
			     !nested_cpu_has_zero_length_injection(vcpu)))
				return VMXERR_ENTRY_INVALID_CONTROL_FIELD;
		}
	}

	return 0;
}