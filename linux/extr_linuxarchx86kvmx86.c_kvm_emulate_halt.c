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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_halt (struct kvm_vcpu*) ; 

int kvm_emulate_halt(struct kvm_vcpu *vcpu)
{
	int ret = kvm_skip_emulated_instruction(vcpu);
	/*
	 * TODO: we might be squashing a GUESTDBG_SINGLESTEP-triggered
	 * KVM_EXIT_DEBUG here.
	 */
	return kvm_vcpu_halt(vcpu) && ret;
}