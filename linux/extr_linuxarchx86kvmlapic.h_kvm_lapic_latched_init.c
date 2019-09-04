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
struct TYPE_4__ {TYPE_1__* apic; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  pending_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_APIC_INIT ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int kvm_lapic_latched_init(struct kvm_vcpu *vcpu)
{
	return lapic_in_kernel(vcpu) && test_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
}