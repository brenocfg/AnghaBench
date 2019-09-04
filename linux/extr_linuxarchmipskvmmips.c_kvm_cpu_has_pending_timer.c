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
struct TYPE_2__ {int /*<<< orphan*/  cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int C_TI ; 
 scalar_t__ kvm_mips_pending_timer (struct kvm_vcpu*) ; 
 int kvm_read_c0_guest_cause (int /*<<< orphan*/ ) ; 

int kvm_cpu_has_pending_timer(struct kvm_vcpu *vcpu)
{
	return kvm_mips_pending_timer(vcpu) ||
		kvm_read_c0_guest_cause(vcpu->arch.cop0) & C_TI;
}