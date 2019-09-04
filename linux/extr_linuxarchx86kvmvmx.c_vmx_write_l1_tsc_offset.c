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
struct vmcs12 {scalar_t__ tsc_offset; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_USE_TSC_OFFSETING ; 
 int /*<<< orphan*/  TSC_OFFSET ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_write_tsc_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_read64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 vmx_write_l1_tsc_offset(struct kvm_vcpu *vcpu, u64 offset)
{
	u64 active_offset = offset;
	if (is_guest_mode(vcpu)) {
		/*
		 * We're here if L1 chose not to trap WRMSR to TSC. According
		 * to the spec, this should set L1's TSC; The offset that L1
		 * set for L2 remains unchanged, and still needs to be added
		 * to the newly set TSC to get L2's TSC.
		 */
		struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
		if (nested_cpu_has(vmcs12, CPU_BASED_USE_TSC_OFFSETING))
			active_offset += vmcs12->tsc_offset;
	} else {
		trace_kvm_write_tsc_offset(vcpu->vcpu_id,
					   vmcs_read64(TSC_OFFSET), offset);
	}

	vmcs_write64(TSC_OFFSET, active_offset);
	return active_offset;
}