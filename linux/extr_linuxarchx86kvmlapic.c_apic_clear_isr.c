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
struct TYPE_3__ {int /*<<< orphan*/  apicv_active; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {scalar_t__ isr_count; int highest_isr_cache; struct kvm_vcpu* vcpu; scalar_t__ regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hwapic_isr_update ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ APIC_ISR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __apic_test_and_clear_vector (int,scalar_t__) ; 
 int /*<<< orphan*/  apic_find_highest_isr (struct kvm_lapic*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void apic_clear_isr(int vec, struct kvm_lapic *apic)
{
	struct kvm_vcpu *vcpu;
	if (!__apic_test_and_clear_vector(vec, apic->regs + APIC_ISR))
		return;

	vcpu = apic->vcpu;

	/*
	 * We do get here for APIC virtualization enabled if the guest
	 * uses the Hyper-V APIC enlightenment.  In this case we may need
	 * to trigger a new interrupt delivery by writing the SVI field;
	 * on the other hand isr_count and highest_isr_cache are unused
	 * and must be left alone.
	 */
	if (unlikely(vcpu->arch.apicv_active))
		kvm_x86_ops->hwapic_isr_update(vcpu,
					       apic_find_highest_isr(apic));
	else {
		--apic->isr_count;
		BUG_ON(apic->isr_count < 0);
		apic->highest_isr_cache = -1;
	}
}