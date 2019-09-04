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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int __kvm_apic_update_irr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

bool kvm_apic_update_irr(struct kvm_vcpu *vcpu, u32 *pir, int *max_irr)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	return __kvm_apic_update_irr(pir, apic->regs, max_irr);
}