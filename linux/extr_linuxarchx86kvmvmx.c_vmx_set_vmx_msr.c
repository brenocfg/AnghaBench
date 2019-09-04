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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  vmcs_enum; } ;
struct TYPE_4__ {TYPE_1__ msrs; scalar_t__ vmxon; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  MSR_IA32_VMX_BASIC 144 
#define  MSR_IA32_VMX_CR0_FIXED0 143 
#define  MSR_IA32_VMX_CR0_FIXED1 142 
#define  MSR_IA32_VMX_CR4_FIXED0 141 
#define  MSR_IA32_VMX_CR4_FIXED1 140 
#define  MSR_IA32_VMX_ENTRY_CTLS 139 
#define  MSR_IA32_VMX_EPT_VPID_CAP 138 
#define  MSR_IA32_VMX_EXIT_CTLS 137 
#define  MSR_IA32_VMX_MISC 136 
#define  MSR_IA32_VMX_PINBASED_CTLS 135 
#define  MSR_IA32_VMX_PROCBASED_CTLS 134 
#define  MSR_IA32_VMX_PROCBASED_CTLS2 133 
#define  MSR_IA32_VMX_TRUE_ENTRY_CTLS 132 
#define  MSR_IA32_VMX_TRUE_EXIT_CTLS 131 
#define  MSR_IA32_VMX_TRUE_PINBASED_CTLS 130 
#define  MSR_IA32_VMX_TRUE_PROCBASED_CTLS 129 
#define  MSR_IA32_VMX_VMCS_ENUM 128 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmx_restore_control_msr (struct vcpu_vmx*,int,int /*<<< orphan*/ ) ; 
 int vmx_restore_fixed0_msr (struct vcpu_vmx*,int,int /*<<< orphan*/ ) ; 
 int vmx_restore_vmx_basic (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int vmx_restore_vmx_ept_vpid_cap (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int vmx_restore_vmx_misc (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmx_set_vmx_msr(struct kvm_vcpu *vcpu, u32 msr_index, u64 data)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * Don't allow changes to the VMX capability MSRs while the vCPU
	 * is in VMX operation.
	 */
	if (vmx->nested.vmxon)
		return -EBUSY;

	switch (msr_index) {
	case MSR_IA32_VMX_BASIC:
		return vmx_restore_vmx_basic(vmx, data);
	case MSR_IA32_VMX_PINBASED_CTLS:
	case MSR_IA32_VMX_PROCBASED_CTLS:
	case MSR_IA32_VMX_EXIT_CTLS:
	case MSR_IA32_VMX_ENTRY_CTLS:
		/*
		 * The "non-true" VMX capability MSRs are generated from the
		 * "true" MSRs, so we do not support restoring them directly.
		 *
		 * If userspace wants to emulate VMX_BASIC[55]=0, userspace
		 * should restore the "true" MSRs with the must-be-1 bits
		 * set according to the SDM Vol 3. A.2 "RESERVED CONTROLS AND
		 * DEFAULT SETTINGS".
		 */
		return -EINVAL;
	case MSR_IA32_VMX_TRUE_PINBASED_CTLS:
	case MSR_IA32_VMX_TRUE_PROCBASED_CTLS:
	case MSR_IA32_VMX_TRUE_EXIT_CTLS:
	case MSR_IA32_VMX_TRUE_ENTRY_CTLS:
	case MSR_IA32_VMX_PROCBASED_CTLS2:
		return vmx_restore_control_msr(vmx, msr_index, data);
	case MSR_IA32_VMX_MISC:
		return vmx_restore_vmx_misc(vmx, data);
	case MSR_IA32_VMX_CR0_FIXED0:
	case MSR_IA32_VMX_CR4_FIXED0:
		return vmx_restore_fixed0_msr(vmx, msr_index, data);
	case MSR_IA32_VMX_CR0_FIXED1:
	case MSR_IA32_VMX_CR4_FIXED1:
		/*
		 * These MSRs are generated based on the vCPU's CPUID, so we
		 * do not support restoring them directly.
		 */
		return -EINVAL;
	case MSR_IA32_VMX_EPT_VPID_CAP:
		return vmx_restore_vmx_ept_vpid_cap(vmx, data);
	case MSR_IA32_VMX_VMCS_ENUM:
		vmx->nested.msrs.vmcs_enum = data;
		return 0;
	default:
		/*
		 * The rest of the VMX capability MSRs do not support restore.
		 */
		return -EINVAL;
	}
}