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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int change_vmcs01_virtual_apic_mode; } ;
struct TYPE_4__ {TYPE_1__ nested; } ;

/* Variables and functions */
#define  LAPIC_MODE_DISABLED 131 
#define  LAPIC_MODE_INVALID 130 
#define  LAPIC_MODE_X2APIC 129 
#define  LAPIC_MODE_XAPIC 128 
 int SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES ; 
 int SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE ; 
 int /*<<< orphan*/  SECONDARY_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ cpu_has_vmx_virtualize_x2apic_mode () ; 
 scalar_t__ flexpriority_enabled ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int kvm_get_apic_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmx_flush_tlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vmx_update_msr_bitmap (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_set_virtual_apic_mode(struct kvm_vcpu *vcpu)
{
	u32 sec_exec_control;

	if (!lapic_in_kernel(vcpu))
		return;

	if (!flexpriority_enabled &&
	    !cpu_has_vmx_virtualize_x2apic_mode())
		return;

	/* Postpone execution until vmcs01 is the current VMCS. */
	if (is_guest_mode(vcpu)) {
		to_vmx(vcpu)->nested.change_vmcs01_virtual_apic_mode = true;
		return;
	}

	sec_exec_control = vmcs_read32(SECONDARY_VM_EXEC_CONTROL);
	sec_exec_control &= ~(SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |
			      SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE);

	switch (kvm_get_apic_mode(vcpu)) {
	case LAPIC_MODE_INVALID:
		WARN_ONCE(true, "Invalid local APIC state");
	case LAPIC_MODE_DISABLED:
		break;
	case LAPIC_MODE_XAPIC:
		if (flexpriority_enabled) {
			sec_exec_control |=
				SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;
			vmx_flush_tlb(vcpu, true);
		}
		break;
	case LAPIC_MODE_X2APIC:
		if (cpu_has_vmx_virtualize_x2apic_mode())
			sec_exec_control |=
				SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE;
		break;
	}
	vmcs_write32(SECONDARY_VM_EXEC_CONTROL, sec_exec_control);

	vmx_update_msr_bitmap(vcpu);
}