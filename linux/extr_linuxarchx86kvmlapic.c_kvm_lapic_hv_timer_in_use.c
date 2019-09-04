#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* apic; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {int hv_timer_in_use; } ;
struct TYPE_5__ {TYPE_1__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 

bool kvm_lapic_hv_timer_in_use(struct kvm_vcpu *vcpu)
{
	if (!lapic_in_kernel(vcpu))
		return false;

	return vcpu->arch.apic->lapic_timer.hv_timer_in_use;
}