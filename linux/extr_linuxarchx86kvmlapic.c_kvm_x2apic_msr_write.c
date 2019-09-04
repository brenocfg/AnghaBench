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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
 int APIC_BASE_MSR ; 
 int APIC_ICR ; 
 int APIC_ICR2 ; 
 int /*<<< orphan*/  apic_x2apic_mode (struct kvm_lapic*) ; 
 int kvm_lapic_reg_write (struct kvm_lapic*,int,int) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 

int kvm_x2apic_msr_write(struct kvm_vcpu *vcpu, u32 msr, u64 data)
{
	struct kvm_lapic *apic = vcpu->arch.apic;
	u32 reg = (msr - APIC_BASE_MSR) << 4;

	if (!lapic_in_kernel(vcpu) || !apic_x2apic_mode(apic))
		return 1;

	if (reg == APIC_ICR2)
		return 1;

	/* if this is ICR write vector before command */
	if (reg == APIC_ICR)
		kvm_lapic_reg_write(apic, APIC_ICR2, (u32)(data >> 32));
	return kvm_lapic_reg_write(apic, reg, (u32)data);
}