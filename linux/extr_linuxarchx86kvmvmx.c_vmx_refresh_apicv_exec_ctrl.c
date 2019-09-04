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
struct vcpu_vmx {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_BASED_VM_EXEC_CONTROL ; 
 int SECONDARY_EXEC_APIC_REGISTER_VIRT ; 
 int SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY ; 
 int /*<<< orphan*/  SECONDARY_VM_EXEC_CONTROL ; 
 scalar_t__ cpu_has_secondary_exec_ctrls () ; 
 scalar_t__ cpu_has_vmx_msr_bitmap () ; 
 scalar_t__ kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_clear_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_pin_based_exec_ctrl (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_update_msr_bitmap (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_refresh_apicv_exec_ctrl(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	vmcs_write32(PIN_BASED_VM_EXEC_CONTROL, vmx_pin_based_exec_ctrl(vmx));
	if (cpu_has_secondary_exec_ctrls()) {
		if (kvm_vcpu_apicv_active(vcpu))
			vmcs_set_bits(SECONDARY_VM_EXEC_CONTROL,
				      SECONDARY_EXEC_APIC_REGISTER_VIRT |
				      SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY);
		else
			vmcs_clear_bits(SECONDARY_VM_EXEC_CONTROL,
					SECONDARY_EXEC_APIC_REGISTER_VIRT |
					SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY);
	}

	if (cpu_has_vmx_msr_bitmap())
		vmx_update_msr_bitmap(vcpu);
}