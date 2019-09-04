#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmx_msr_entry {int index; scalar_t__ reserved; } ;
struct TYPE_2__ {int apic_base; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int MSR_IA32_UCODE_REV ; 
 int MSR_IA32_UCODE_WRITE ; 
 int X2APIC_ENABLE ; 

__attribute__((used)) static int nested_vmx_msr_check_common(struct kvm_vcpu *vcpu,
				       struct vmx_msr_entry *e)
{
	/* x2APIC MSR accesses are not allowed */
	if (vcpu->arch.apic_base & X2APIC_ENABLE && e->index >> 8 == 0x8)
		return -EINVAL;
	if (e->index == MSR_IA32_UCODE_WRITE || /* SDM Table 35-2 */
	    e->index == MSR_IA32_UCODE_REV)
		return -EINVAL;
	if (e->reserved != 0)
		return -EINVAL;
	return 0;
}