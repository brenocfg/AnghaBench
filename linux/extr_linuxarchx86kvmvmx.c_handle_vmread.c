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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct vmcs12 {unsigned long long vmcs_link_pointer; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 int /*<<< orphan*/  VMXERR_UNSUPPORTED_VMCS_COMPONENT ; 
 int /*<<< orphan*/  VMX_INSTRUCTION_INFO ; 
 struct vmcs12* get_shadow_vmcs12 (struct kvm_vcpu*) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ get_vmx_mem_address (struct kvm_vcpu*,unsigned long,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 unsigned long kvm_register_readl (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_register_writel (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_write_guest_virt_system (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_check_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_failValid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_vmx_succeed (struct kvm_vcpu*) ; 
 scalar_t__ vmcs12_read_any (struct vmcs12*,unsigned long,int /*<<< orphan*/ *) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_vmread(struct kvm_vcpu *vcpu)
{
	unsigned long field;
	u64 field_value;
	unsigned long exit_qualification = vmcs_readl(EXIT_QUALIFICATION);
	u32 vmx_instruction_info = vmcs_read32(VMX_INSTRUCTION_INFO);
	gva_t gva = 0;
	struct vmcs12 *vmcs12;

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (!nested_vmx_check_vmcs12(vcpu))
		return kvm_skip_emulated_instruction(vcpu);

	if (!is_guest_mode(vcpu))
		vmcs12 = get_vmcs12(vcpu);
	else {
		/*
		 * When vmcs->vmcs_link_pointer is -1ull, any VMREAD
		 * to shadowed-field sets the ALU flags for VMfailInvalid.
		 */
		if (get_vmcs12(vcpu)->vmcs_link_pointer == -1ull) {
			nested_vmx_failInvalid(vcpu);
			return kvm_skip_emulated_instruction(vcpu);
		}
		vmcs12 = get_shadow_vmcs12(vcpu);
	}

	/* Decode instruction info and find the field to read */
	field = kvm_register_readl(vcpu, (((vmx_instruction_info) >> 28) & 0xf));
	/* Read the field, zero-extended to a u64 field_value */
	if (vmcs12_read_any(vmcs12, field, &field_value) < 0) {
		nested_vmx_failValid(vcpu, VMXERR_UNSUPPORTED_VMCS_COMPONENT);
		return kvm_skip_emulated_instruction(vcpu);
	}
	/*
	 * Now copy part of this value to register or memory, as requested.
	 * Note that the number of bits actually copied is 32 or 64 depending
	 * on the guest's mode (32 or 64 bit), not on the given field's length.
	 */
	if (vmx_instruction_info & (1u << 10)) {
		kvm_register_writel(vcpu, (((vmx_instruction_info) >> 3) & 0xf),
			field_value);
	} else {
		if (get_vmx_mem_address(vcpu, exit_qualification,
				vmx_instruction_info, true, &gva))
			return 1;
		/* _system ok, nested_vmx_check_permission has verified cpl=0 */
		kvm_write_guest_virt_system(vcpu, gva, &field_value,
					    (is_long_mode(vcpu) ? 8 : 4), NULL);
	}

	nested_vmx_succeed(vcpu);
	return kvm_skip_emulated_instruction(vcpu);
}