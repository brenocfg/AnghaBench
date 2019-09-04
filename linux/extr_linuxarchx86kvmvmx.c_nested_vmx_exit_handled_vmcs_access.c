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
typedef  unsigned long u8 ;
typedef  int u32 ;
struct vmcs12 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMX_INSTRUCTION_INFO ; 
 unsigned long kvm_register_read (struct kvm_vcpu*,int) ; 
 scalar_t__ kvm_vcpu_read_guest (struct kvm_vcpu*,scalar_t__,unsigned long*,int) ; 
 int /*<<< orphan*/  nested_cpu_has_shadow_vmcs (struct vmcs12*) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nested_vmx_exit_handled_vmcs_access(struct kvm_vcpu *vcpu,
	struct vmcs12 *vmcs12, gpa_t bitmap)
{
	u32 vmx_instruction_info;
	unsigned long field;
	u8 b;

	if (!nested_cpu_has_shadow_vmcs(vmcs12))
		return true;

	/* Decode instruction info and find the field to access */
	vmx_instruction_info = vmcs_read32(VMX_INSTRUCTION_INFO);
	field = kvm_register_read(vcpu, (((vmx_instruction_info) >> 28) & 0xf));

	/* Out-of-range fields always cause a VM exit from L2 to L1 */
	if (field >> 15)
		return true;

	if (kvm_vcpu_read_guest(vcpu, bitmap + field/8, &b, 1))
		return true;

	return 1 & (b >> (field & 7));
}